package pa2;

import java.util.Comparator;

class Element {

	public int item;
	public int priority;
	
	public Element(int item, int priority) {
		this.item = item;
		this.priority = priority;
	}
}

class ElementComparator implements Comparator<Element> {

	@Override
	public int compare(Element o1, Element o2) {
		return o1.priority - o2.priority;
	}

}
