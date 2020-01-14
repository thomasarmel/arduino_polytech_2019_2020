package pancakeDrawer;

import java.awt.Color;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.List;

import javax.swing.JOptionPane;
import javax.swing.JProgressBar;

public class TCPClient {
	private String host;
	private short port;
	private PDWindow parent;
	private JProgressBar parentProgressBar;
	public TCPClient() {}
	
	public TCPClient(String host, short port) {
		this.host=host;
		this.port=port;
	}
	
	void setParent(PDWindow parent) {
		this.parent=parent;
		parentProgressBar=parent.getSendPointsProgressBar();
	}
	
	public void sendListPoints(List<PDPoint> listPoints) throws Exception {
		try (Socket socket = new Socket(this.host, this.port)) {
			parentProgressBar.setValue(0);
			parentProgressBar.setString("0 %");
			parentProgressBar.setForeground(Color.cyan);
			OutputStream output = socket.getOutputStream();
			PrintWriter writer = new PrintWriter(output, true);
			int i=0;
			int percentProgress=0;
			for(PDPoint p : listPoints) {
				writer.println("point:"+p.getX()+","+p.getY());
				percentProgress=(i*100)/listPoints.size();
				parentProgressBar.setValue(percentProgress);
				parentProgressBar.setString(percentProgress+" %");
				Thread.sleep(100);
				i++;
			}
			writer.println("point:done");
			parentProgressBar.setValue(100);
			parentProgressBar.setString("100 %");
			parentProgressBar.setForeground(Color.green);
		} catch (UnknownHostException ex) {
			throw ex;
		} catch (IOException ex) {
			throw ex;
		}
	}
	
	public void sendDone() throws Exception {
		try (Socket socket = new Socket(this.host, this.port)) {
			OutputStream output = socket.getOutputStream();
			PrintWriter writer = new PrintWriter(output, true);
			writer.println("point:done");
		} catch (UnknownHostException ex) {
			JOptionPane.showMessageDialog(parent, "Erreur réseau: UnknownHostException.", "Erreur réseau", JOptionPane.ERROR_MESSAGE);
			return;
		} catch (IOException ex) {
			JOptionPane.showMessageDialog(parent, "Erreur réseau: IOException.", "Erreur réseau", JOptionPane.ERROR_MESSAGE);
			return;
		}
		JOptionPane.showMessageDialog(parent, "Task done.", "Done", JOptionPane.INFORMATION_MESSAGE);
	}
}
