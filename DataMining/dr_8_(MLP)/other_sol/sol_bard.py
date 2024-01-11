import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

class Neuron:
    def __init__(self, n_inputs, activation_function):
        self.weights = np.random.uniform(-0.05, 0.05, (n_inputs, 1))
        self.bias = np.random.uniform(-0.05, 0.05)
        self.activation_function = activation_function

    def forward(self, inputs):
        weighted_sum = np.dot(inputs, self.weights) + self.bias
        return self.activation_function(weighted_sum)

class NeuralNetwork:
    def __init__(self, n_inputs, n_hidden, n_outputs, activation_function):
        self.input_layer = []
        for _ in range(n_inputs):
            self.input_layer.append(Neuron(n_inputs, activation_function))

        self.hidden_layer = []
        for _ in range(n_hidden):
            self.hidden_layer.append(Neuron(n_inputs, activation_function))

        self.output_layer = []
        for _ in range(n_outputs):
            self.output_layer.append(Neuron(n_hidden, activation_function))

    def forward(self, inputs):
        x = inputs
        for neuron in self.input_layer:
            x = neuron.forward(x)
        for neuron in self.hidden_layer:
            x = neuron.forward(x)
        for neuron in self.output_layer:
            x = neuron.forward(x)
        return x

    def backpropagate(self, inputs, expected_outputs, learning_rate):
        outputs = self.forward(inputs)

        # Compute errors for output layer neurons
        output_errors = expected_outputs - outputs

        # Compute errors for hidden layer neurons
        hidden_errors = []
        for i, neuron in enumerate(self.hidden_layer):
            hidden_error = 0
            for j, output_neuron in enumerate(self.output_layer):
                hidden_error += output_errors[j] * output_neuron.weights[i]
            hidden_errors.append(hidden_error)

        # Update weights for output layer neurons
        for i, output_neuron in enumerate(self.output_layer):
            output_neuron.weights += learning_rate * output_errors[i] * outputs

        # Update weights for hidden layer neurons
        for i, hidden_neuron in enumerate(self.hidden_layer):
            hidden_neuron.weights += learning_rate * hidden_errors[i] * hidden_neuron.activation_function(x[i])

    def train(self, inputs, expected_outputs, epochs, learning_rate):
        for _ in range(epochs):
            for inputs, expected_outputs in zip(inputs, expected_outputs):
                self.backpropagate(inputs, expected_outputs, learning_rate)

    def predict(self, inputs):
        return self.forward(inputs)

# Инициализираме данните
inputs_and = [[1, 1], [1, 0], [0, 1], [0, 0]]
expected_outputs_and = [1, 0, 0, 0]

inputs_or = [[1, 1], [1, 0], [0, 1], [0, 0]]
expected_outputs_or = [1, 1, 1, 0]

inputs_xor = [[1, 1], [1, 0], [0, 1], [0, 0]]
expected_outputs_xor = [0, 1, 1, 0]

# Инициализираме невронните мрежи
and_network = NeuralNetwork(2, 1, 1, sigmoid)
or_network = NeuralNetwork(2, 1, 1, sigmoid)
xor_network = NeuralNetwork(2, 2, 1, sigmoid)

# Обучаваме невронните мрежи
and_network.train(inputs_and, expected_outputs_and, 10000, 0.01)
or_network.train(inputs_or, expected_outputs_or, 10000, 0.01)
xor_network.train(inputs_xor, expected_outputs_xor, 10000, 0.01)

# Тестваме невронните мрежи
for inputs, expected_outputs in zip(inputs_and, expected_outputs_and):
    print("AND: inputs:", inputs, "expected:", expected_outputs, "actual:", and_network.predict(inputs))

for inputs, expected_outputs in zip(inputs_or, expected_outputs_or):
    print("OR: inputs:", inputs, "expected:", expected_outputs, "actual:", or_network.predict(inputs))

for inputs, expected_outputs in zip(inputs_xor, expected_outputs_xor):
    print("XOR: inputs:", inputs, "expected:", expected_outputs, "actual:", xor_network.predict(inputs))