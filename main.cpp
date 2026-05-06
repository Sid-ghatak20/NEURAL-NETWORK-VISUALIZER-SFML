#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
using namespace std;
using namespace sf;
		
//----------------------------------------------------------------------define struct : -----------------------------------------------------------------------//
struct Neuron {
	float value; //activation value
	float bias;
	vector<float> weights;
};
//-------------------------------------------------------------------FORWARD PASS FUNCTION--------------------------------------------------------------------//
float activate(float x)
{
	return 1.0f / (1.0f + exp(-x)); //sigmoid function
}

void forward(vector<vector<Neuron>>& network)
{
	//STEP 1: LOOP OVER LAYERS


	for (int i = 0; i < network.size() - 1; i++)  //except last layer, since last layer has no forward layer
	{
		//reset next layer values in every loop.
		for (int k = 0; k < network[i + 1].size(); k++)
		{
			network[i + 1][k].value = 0.0f;
		}



		//STEP 2: LOOP OVER NEURONS OF FIRST LAYER AND ACCESS EACH NEURON OF THE LAYER



		for (int j = 0; j < network[i].size(); j++)
		{
			Neuron& current = network[i][j]; //assign the pointer to access stored neuron inside network



			//STEP 3: LOOP OVER NEXT LAYER'S NEURONS ONE AFTER ANOTHER AND use the formula: σ(i=1∑n​(xi​⋅wi​)+b)

			//accumulate weighted sums: 
			for (int k = 0; k < network[i + 1].size(); k++)
			{
				Neuron& next = network[i + 1][k];
				next.value += current.value * current.weights[k];
				//[k] will  index over and access: [0.37, 0.78. 0.63] using k=0=0.37, k=1=0.78, k=3=0.63 
			}
		}
		//apply activation and bias outside loop as we only loop the summation part, bias and activation is applied over enitre summation
		for (int k = 0; k < network[i + 1].size(); k++)
		{
			Neuron& next = network[i + 1][k];

			next.value += next.bias;
			next.value = activate(next.value);
		}
	}

}

int main() {
	RenderWindow window(VideoMode(1920, 1080), "Neural Network Visualizer");
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
		neuron.setFillColor(Color::Green);
		neuron.setPosition(400, 200 + i * 100);
		neurons.push_back (neuron);

	}
	//output later: 1 neuron
	CircleShape OutputNeuron(20);
	OutputNeuron.setFillColor(Color::Red);
	OutputNeuron.setPosition(700, 300);
	neurons.push_back(OutputNeuron);



//---------------------------------------------------LOGICAL NETWORK--------------------------------------------------------------//
	


// BUILDING NETWORK: 
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
	}
			//INPUT INJECTION:
			network[0][0].value = 1.0f;
			network[0][1].value = 0.5f;
			forward(network);	

		//-----------------------------------------------MAIN GAME LOOP----------------------------------------------------------//

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();
			}

			window.clear(Color::Black);

			for (auto& neuron : neurons) {
				window.draw(neuron);
			}

			window.display();
		}
	}


