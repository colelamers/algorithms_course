#ifndef ELEMENT_H_
#define ELEMENT_H_

class Element {

public:

	int item;
	int priority;
    
    Element() {
        
    }

	Element(int item, int priority) {
		this->item = item;
		this->priority = priority;
	}
};

class ElementComparator {

public:

    bool operator()(const Element &arg1, const Element &arg2) const {
        return arg1.priority > arg2.priority;
    }
};

#endif /* ELEMENT_H_ */
