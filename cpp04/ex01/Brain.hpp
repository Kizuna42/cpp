#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain {
private:
	static const int IDEA_COUNT = 100;
	std::string ideas[IDEA_COUNT];

public:
	Brain(void);
	Brain(const Brain& other);
	Brain& operator=(const Brain& other);
	~Brain(void);

	void setIdea(int index, const std::string& idea);
	std::string getIdea(int index) const;
	void printIdeas(int count = 5) const;
};

#endif
