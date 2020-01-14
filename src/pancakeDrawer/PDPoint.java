package pancakeDrawer;

import java.awt.Color;
import java.io.Serializable;

public class PDPoint implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = -633480762946283491L;
	private int x;
	private int y;
	private int size;
	private Color color;
	
	public PDPoint(int x, int y, int size, Color color) {
		this.x=x;
		this.y=y;
		this.size=size;
		this.color=color;
	}
	
	public int getX() {
		return this.x;
	}
	public int getY() {
		return this.y;
	}
	public int getSize() {
		return this.size;
	}
	public Color getColor() {
		return this.color;
	}
}
