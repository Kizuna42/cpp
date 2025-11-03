#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void) {
	std::cout << "MateriaSource constructor called" << std::endl;
	for (int i = 0; i < MATERIA_COUNT; i++) {
		this->templates[i] = 0;
	}
}

MateriaSource::MateriaSource(const MateriaSource& other) {
	std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < MATERIA_COUNT; i++) {
		if (other.templates[i]) {
			this->templates[i] = other.templates[i]->clone();
		} else {
			this->templates[i] = 0;
		}
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
	std::cout << "MateriaSource assignment operator called" << std::endl;
	if (this != &other) {
		for (int i = 0; i < MATERIA_COUNT; i++) {
			if (this->templates[i]) {
				delete this->templates[i];
				this->templates[i] = 0;
			}
		}

		for (int i = 0; i < MATERIA_COUNT; i++) {
			if (other.templates[i]) {
				this->templates[i] = other.templates[i]->clone();
			} else {
				this->templates[i] = 0;
			}
		}
	}
	return *this;
}

MateriaSource::~MateriaSource(void) {
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < MATERIA_COUNT; i++) {
		if (this->templates[i]) {
			delete this->templates[i];
		}
	}
}

void MateriaSource::learnMateria(AMateria* m) {
	if (!m) {
		std::cout << "Cannot learn null materia!" << std::endl;
		return;
	}

	for (int i = 0; i < MATERIA_COUNT; i++) {
		if (!this->templates[i]) {
			this->templates[i] = m;
			std::cout << "MateriaSource learned " << m->getType() << " in slot " << i << std::endl;
			return;
		}
	}

	std::cout << "MateriaSource is full! Cannot learn " << m->getType() << std::endl;
	delete m;
}

AMateria* MateriaSource::createMateria(const std::string& type) {
	for (int i = 0; i < MATERIA_COUNT; i++) {
		if (this->templates[i] && this->templates[i]->getType() == type) {
			std::cout << "MateriaSource creating " << type << std::endl;
			return this->templates[i]->clone();
		}
	}

	std::cout << "MateriaSource doesn't know " << type << std::endl;
	return 0;
}

void MateriaSource::printTemplates(void) const {
	std::cout << "MateriaSource templates:" << std::endl;
	for (int i = 0; i < MATERIA_COUNT; i++) {
		std::cout << "  [" << i << "] ";
		if (this->templates[i]) {
			std::cout << this->templates[i]->getType();
		} else {
			std::cout << "empty";
		}
		std::cout << std::endl;
	}
}
