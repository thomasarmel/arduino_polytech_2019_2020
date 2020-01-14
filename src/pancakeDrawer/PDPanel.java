package pancakeDrawer;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;

public class PDPanel extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = -5129269703029893747L;
	private List<PDPoint> listePoints=new ArrayList<PDPoint>();
	
	public void paintComponent(Graphics g) {
		g.setColor(Color.white);
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
		for(PDPoint p : listePoints) {
			g.setColor(p.getColor());
			g.fillOval(p.getX(), p.getY(), p.getSize(), p.getSize());
		}
	}
	
	public void addPoint(PDPoint p) {
		listePoints.add(p);
	}
	
	public void clear() {
		listePoints.clear();
	}
	
	public List<PDPoint> getListPoints() {
		return listePoints;
	}
	
	void setListPoints(List<PDPoint> listPoints) {
		this.listePoints=new ArrayList<>(listPoints);
	}
}
