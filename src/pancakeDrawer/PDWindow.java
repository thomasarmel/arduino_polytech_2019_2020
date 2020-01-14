package pancakeDrawer;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.List;

import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.KeyStroke;
import javax.swing.SwingConstants;

public class PDWindow extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 6333482738439920830L;
	private JPanel container = new JPanel();
	private PDPanel pan = new PDPanel();
	private DragListener dragListener=new DragListener();
	private JMenuBar menuBar=new JMenuBar();
	private JMenu menuFichier=new JMenu("Fichier");
	private JMenuItem menuItemEffacer=new JMenuItem("Effacer");
	private JMenuItem menuItemEnregistrer=new JMenuItem("Enregistrer");
	private JMenuItem menuItemOuvrir=new JMenuItem("Ouvrir...");
	private JMenuItem menuItemEnvoyer=new JMenuItem("Envoyer à l'Arduino");
	private JMenuItem menuItemQuitter=new JMenuItem("Quitter");
	private PDWindow thisWindow=this;
	JProgressBar sendPointsProgressBar=new JProgressBar(SwingConstants.HORIZONTAL, 0, 100);
	
	private Color color=Color.orange;
	
	public PDWindow() {
		this.setTitle("Pancake drawer");
		this.setSize(1000, 1000);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		
		pan.addMouseMotionListener(dragListener);
		
		container.setBackground(Color.white);
		container.setLayout(new BorderLayout());
		
		container.add(pan, BorderLayout.CENTER);
		container.add(sendPointsProgressBar, BorderLayout.SOUTH);
		
		this.setContentPane(container);
		sendPointsProgressBar.setValue(0);
		sendPointsProgressBar.setStringPainted(true);
		sendPointsProgressBar.setString("0 %");
		sendPointsProgressBar.setForeground(Color.cyan);
		this.initMenu();
		this.setVisible(true);
	}
	
	private void initMenu() {
		menuItemEffacer.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_DOWN_MASK));
		menuItemOuvrir.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, KeyEvent.CTRL_DOWN_MASK));
		menuItemEnregistrer.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_DOWN_MASK));
		menuItemQuitter.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, KeyEvent.CTRL_DOWN_MASK));
		menuFichier.setMnemonic('F');
		menuItemEffacer.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				pan.clear();
				pan.repaint();
			}
		});
		menuItemQuitter.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
				
			}
		});
		menuItemOuvrir.addActionListener(new OpenListener());
		menuItemEnregistrer.addActionListener(new SaveListener());
		menuItemEnvoyer.addActionListener(new SendListener());
		
		menuFichier.add(menuItemEffacer);
		menuFichier.add(menuItemOuvrir);
		menuFichier.add(menuItemEnregistrer);
		menuFichier.add(menuItemEnvoyer);
		menuFichier.addSeparator();
		menuFichier.add(menuItemQuitter);
		
		menuBar.add(menuFichier);
		this.setJMenuBar(menuBar);
	}
	
	JProgressBar getSendPointsProgressBar() {
		return this.sendPointsProgressBar;
	}
	
	class SaveListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			JFrame parentFrame = new JFrame();
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setDialogTitle("Sauvegarder votre croquis...");   
			int userSelection = fileChooser.showSaveDialog(parentFrame);
			if (userSelection == JFileChooser.APPROVE_OPTION) {
			    File fileToSave = fileChooser.getSelectedFile();
			    try {
			    	ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(fileToSave)));
			    	oos.writeObject(pan.getListPoints());
			    	oos.close();
			    } catch(IOException ex) {
			    	JOptionPane.showMessageDialog(thisWindow, "Impossible de sauvegarder votre croquis.\nAvez-vous les permissions nécessaires ?", "Sauvegarde impossible", JOptionPane.ERROR_MESSAGE);
			    }
			}
		}
	}
	
	class OpenListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			JFrame parentFrame = new JFrame();
			JFileChooser fileChooser = new JFileChooser();
			int result = fileChooser.showOpenDialog(parentFrame);
			if (result == JFileChooser.APPROVE_OPTION) {
			    File selectedFile = fileChooser.getSelectedFile();
			    try {
			    	ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(new FileInputStream(selectedFile)));
			    	try {
			    		@SuppressWarnings("unchecked")
			    		List<PDPoint> listPoints = (List<PDPoint>)ois.readObject();
			    		pan.setListPoints(listPoints);
			    		pan.repaint();
			    	} catch(ClassNotFoundException ex) {
			    		ex.printStackTrace();
			    	}
			    	ois.close();
			    } catch(FileNotFoundException ex) {
			    	JOptionPane.showMessageDialog(thisWindow, "Le fichier spécifié est introuvable.", "Fichier introuvable", JOptionPane.ERROR_MESSAGE);
			    } catch(IOException ex) {
			    	JOptionPane.showMessageDialog(thisWindow, "Impossible d'ouvrir le croquis.\nAvez-vous les permissions nécessaires ?", "Ouverture impossible", JOptionPane.ERROR_MESSAGE);
			    }
			}
		}
	}
	
	class SendListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			Thread threadSendToArduino = new Thread() {
				public void run() {
					try {
						TCPClient tcpClient=new TCPClient("192.168.4.1", (short)8122);
						tcpClient.setParent(thisWindow);
						tcpClient.sendListPoints(pan.getListPoints());
					} catch(Exception ex) {
						JOptionPane.showMessageDialog(thisWindow, "Impossible d'envoyer les données à l'Arduino.", "Erreur réseau", JOptionPane.ERROR_MESSAGE);
					}
				}
			};
			threadSendToArduino.start();
		}
	}
	
	class DragListener implements MouseMotionListener {
		public void mouseMoved(MouseEvent e) {
			//
		}
		public void mouseDragged(MouseEvent e) {
			pan.addPoint(new PDPoint(e.getX(), e.getY(), 50, color));
			pan.repaint();
		}
	}
}
