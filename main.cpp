#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
using namespace std;
using namespace sf;
int main() {
	RenderWindow window(VideoMode(1000, 700), "Neural Network Visualizer");
	//set frame rate limit for smooth animations
	window.setFramerateLimit(60);
	
	//NEURONS :
	vector <CircleShape> neurons; //NOTE THIS IS VECTOR ARRAY NEURON

	//Input layer: 2 neurons
	
	for (int i = 0; i < 2; i++) {
		CircleShape neuron(20);				//THIS JUST NEURON OBJECT
		neuron.setFillColor(Color::Red);
		neuron.setPosition(100, 200 + i * 100);
		neurons.push_back(neuron);			//THE NEURON OBJECT IS PUSHED INTO THE VECTOR ARRAY NEURON
	}

	//hidden layer: 3 neurons
	for (int i = 0; i < 3; i++) {
		CircleShape neuron(20);
		neuron.setFillColor(Color::Blue);
		neuron.setPosition(400, 150 + i * 300);
		neurons.push_back (neuron);

	}
	//output later: 1 neuron
	CircleShape OutputNeuron(20);
	OutputNeuron.setFillColor(Color::Red);
	OutputNeuron.setPosition(700, 300);
	neurons.push_back(OutputNeuron);

	vector < CircleShape> neuron(20);

	//main game loop:

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
			}
	}

	window.clear(Color::Black);

	for(auto &neuron : neurons) {
		window.draw(neuron);
	}
	
	window.display();



}