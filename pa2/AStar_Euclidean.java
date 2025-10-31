package pa2;

public class AStar_Euclidean extends AStar {

	public AStar_Euclidean(Graph g) {
		super(g);
	}

	protected int heuristic(int v, int target) {
		// Similar to pa2.LandmarkGenerator.euclidean
		double diffX = coordinates.get(v).x - coordinates.get(target).x;
		double diffY = coordinates.get(v).y - coordinates.get(target).y;
		return (int) Math.sqrt(diffX * diffX + diffY * diffY);
	}
}
