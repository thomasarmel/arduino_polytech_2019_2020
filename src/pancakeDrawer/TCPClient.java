package pancakeDrawer;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.List;

public class TCPClient {
	private String host;
	private short port;
	public TCPClient() {}
	
	public TCPClient(String host, short port) {
		this.host=host;
		this.port=port;
	}
	
	public void sendListPoints(List<PDPoint> listPoints) throws Exception {
		try (Socket socket = new Socket(this.host, this.port)) {
			OutputStream output = socket.getOutputStream();
			PrintWriter writer = new PrintWriter(output, true);
			for(PDPoint p : listPoints) {
				writer.println("point:"+p.getX()+","+p.getY());
			}
			writer.println("point:done");
		} catch (UnknownHostException ex) {
			throw ex;
		} catch (IOException ex) {
			throw ex;
		}
	}
}
