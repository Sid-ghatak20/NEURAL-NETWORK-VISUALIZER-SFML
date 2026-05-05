#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
using namespace std;
using namespace sf;
int main() {
	RenderWindow window(VideoMode(1000, 700), "Neural Network Visualizer");
	//set frame rate limit for smooth animations
	window.setFramerateLimit(60);
	
	//------------------------------------------------VISUAL NEURONS FOR SFML------------------------------------------------------//




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



//---------------------------------------------------LOGICAL NETWORK--------------------------------------------------------------//
	


// BUILDING NETWORK: 
	//define struct : 
	struct Neuron {
		float value; //activation value
		float bias;
		vector<float> weights;
	};
	//Create a vector LayerSize: HARDCODED for now
	vector<int> layerSize = { 2,3,1 }; //2 input neurons, 3 hidden neurons, 1 output neuron 

	//create network: 
	vector<vector<Neuron>> network; //vector of layers, each layer is a vector of neurons

	for (int i = 0; i < layerSize.size(); i++) {
		vector <Neuron> layer;
		{
			for (int j = 0; j < layerSize[i]; j++)
			{
				Neuron n; //create object n of class neuron
				n.value = 0.0f; //set value for activation
				n.bias = 0.0f;	// set bias

				//for attribute weight, which is a dynamic array:
					//1. find number of nodes in next layer
					//2. generate random weights for that many nodes of next layer
				if (i < layerSize.size() - 1) //assign weights to all nodes except output.
				{
					int nextSize = layerSize[i + 1];

					for (int k = 0; k < nextSize; k++) {
						n.weights.push_back((rand() % 100) / 100.0f); //random [0,1]

						//push weights generate in k variable into weight attribute 
					}
				}
				layer.push_back(n); //push neuron generated in j variable to layer vector dynamic array

			}
			network.push_back(layer); //push neuron generate in i variable to network vector dynamic array
		}



	//-----------------------------------------------MAIN GAME LOOP----------------------------------------------------------//

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
			}

		window.clear(Color::Black);

		for (auto& neuron : neurons) {
			window.draw(neuron);
		}

		window.display();
	}

}



}
