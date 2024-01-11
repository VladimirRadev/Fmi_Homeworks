import numpy as np

class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size

        # Инициализация на теглата със случайни стойности от интервала (-0.05, 0.05)
        self.weights_input_hidden = np.random.uniform(-0.05, 0.05, (self.input_size, self.hidden_size))
        self.weights_hidden_output = np.random.uniform(-0.05, 0.05, (self.hidden_size, self.output_size))

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def train(self, inputs, targets, learning_rate=0.9, epochs=50000):
        for epoch in range(epochs):
            # Forward pass
            hidden_inputs = np.dot(inputs, self.weights_input_hidden)
            hidden_outputs = self.sigmoid(hidden_inputs)

            final_inputs = np.dot(hidden_outputs, self.weights_hidden_output)
            final_outputs = self.sigmoid(final_inputs)

            # Backpropagation
            output_errors = targets - final_outputs
            output_delta = output_errors * self.sigmoid_derivative(final_outputs)

            hidden_errors = output_delta.dot(self.weights_hidden_output.T)
            hidden_delta = hidden_errors * self.sigmoid_derivative(hidden_outputs)

            # Update weights
            self.weights_hidden_output += learning_rate * hidden_outputs.T.dot(output_delta)
            self.weights_input_hidden += learning_rate * inputs.T.dot(hidden_delta)

    def predict(self, inputs):
        hidden_inputs = np.dot(inputs, self.weights_input_hidden)
        hidden_outputs = self.sigmoid(hidden_inputs)

        final_inputs = np.dot(hidden_outputs, self.weights_hidden_output)
        final_outputs = self.sigmoid(final_inputs)

        return final_outputs

# AND гейт
and_inputs = np.array([[1, 1], [0, 1], [1, 0], [0, 0]])
and_targets = np.array([[1], [0], [0], [0]])

and_nn = NeuralNetwork(input_size=2, hidden_size=4, output_size=1)
and_nn.train(and_inputs, and_targets)

print("AND Gate:")
for i in range(len(and_inputs)):
    prediction = and_nn.predict(and_inputs[i])
    print(f"Inputs: {and_inputs[i]}, Expected: {and_targets[i][0]}, Actual: {prediction[0]}")

# OR гейт
or_inputs = np.array([[1, 1], [0, 1], [1, 0], [0, 0]])
or_targets = np.array([[1], [1], [1], [0]])

or_nn = NeuralNetwork(input_size=2, hidden_size=4, output_size=1)
or_nn.train(or_inputs, or_targets)

print("\nOR Gate:")
for i in range(len(or_inputs)):
    prediction = or_nn.predict(or_inputs[i])
    print(f"Inputs: {or_inputs[i]}, Expected: {or_targets[i][0]}, Actual: {prediction[0]}")

# XOR гейт
xor_inputs = np.array([[1, 1], [0, 1], [1, 0], [0, 0]])
xor_targets = np.array([[0], [1], [1], [0]])

xor_nn = NeuralNetwork(input_size=2, hidden_size=4, output_size=1)
xor_nn.train(xor_inputs, xor_targets)

print("\nXOR Gate:")
for i in range(len(xor_inputs)):
    prediction = xor_nn.predict(xor_inputs[i])
    print(f"Inputs: {xor_inputs[i]}, Expected: {xor_targets[i][0]}, Actual: {prediction[0]}")