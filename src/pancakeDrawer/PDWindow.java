package pancakeDrawer;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.KeyStroke;

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
	private JMenuItem menuItemQuitter=new JMenuItem("Quitter");
	
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
		
		this.setContentPane(container);
		this.initMenu();
		this.setVisible(true);
	}
	
	private void initMenu() {
		menuItemEffacer.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_DOWN_MASK));
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
		menuItemEnregistrer.addActionListener(new SaveListener());
		
		menuFichier.add(menuItemEffacer);
		menuFichier.add(menuItemEnregistrer);
		menuFichier.addSeparator();
		menuFichier.add(menuItemQuitter);
		
		menuBar.add(menuFichier);
		this.setJMenuBar(menuBar);
	}
	
	class SaveListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			
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
