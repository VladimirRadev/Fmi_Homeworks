import math
import random

class Neuron:
    counter = 0

    def __init__(self):
        Neuron.counter += 1
        self.id = Neuron.counter
        self.bias_connection = None
        self.bias = -1
        self.output = 0
        self.in_connections = []
        self.connection_lookup = {}

    def calculate_output(self):
        s = 0
        for connection in self.in_connections:
            left_neuron = connection.get_from_neuron()
            weight = connection.get_weight()
            a = left_neuron.get_output()
            s += weight * a
        s += self.bias_connection.get_weight() * self.bias
        self.output = self.g(s)

    def g(self, x):
        return self.sigmoid(x)

    def sigmoid(self, x):
        return 1.0 / (1.0 + math.exp(-x))

    def add_in_connections(self, in_neurons):
        for neuron in in_neurons:
            connection = Connection(neuron, self)
            self.in_connections.append(connection)
            self.connection_lookup[neuron.id] = connection

    def get_connection(self, neuron_index):
        return self.connection_lookup.get(neuron_index)

    def add_in_connection(self, connection):
        self.in_connections.append(connection)

    def add_bias_connection(self, neuron):
        connection = Connection(neuron, self)
        self.bias_connection = connection
        self.in_connections.append(connection)

    def get_all_in_connections(self):
        return self.in_connections

    def get_bias(self):
        return self.bias

    def get_output(self):
        return self.output
    def set_output(self, output):
        self.output = output

class Connection:
    counter = 0

    def __init__(self, from_neuron, to_neuron):
        Connection.counter += 1
        self.id = Connection.counter
        self.weight = 0
        self.prev_delta_weight = 0
        self.delta_weight = 0
        self.left_neuron = from_neuron
        self.right_neuron = to_neuron

    def get_weight(self):
        return self.weight

    def set_weight(self, w):
        self.weight = w

    def set_delta_weight(self, w):
        self.prev_delta_weight = self.delta_weight
        self.delta_weight = w

    def get_prev_delta_weight(self):
        return self.prev_delta_weight

    def get_from_neuron(self):
        return self.left_neuron

    def get_to_neuron(self):
        return self.right_neuron
class NeuralNetwork_AND:
    def __init__(self, input_size, hidden_size, output_size):
        self.is_trained = False
        self.df = 0.0
        self.rand = random.Random()
        self.input_layer = []
        self.hidden_layer = []
        self.output_layer = []
        self.bias = Neuron()
        self.layers = [input_size, hidden_size, output_size]
        self.random_weight_multiplier = 1
        self.epsilon = 0.00000000001
        self.learning_rate = 0.9
        self.momentum = 0.7
        self.inputs = [[1, 1], [1, 0], [0, 1], [0, 0]]
        self.expected_outputs = [[1], [0], [0], [0]]
        self.result_outputs = [[-1], [-1], [-1], [-1]]
        self.output = None
        self.weight_update = {}

        self.initialize_neurons()

    def initialize_neurons(self):
        for i in range(len(self.layers)):
            layer_neurons = []
            if i == 0:
                layer_neurons = [Neuron() for _ in range(self.layers[i])]
                self.input_layer = layer_neurons
            elif i == 1:
                for _ in range(self.layers[i]):
                    neuron = Neuron()
                    neuron.add_in_connections(self.input_layer)
                    neuron.add_bias_connection(self.bias)
                    layer_neurons.append(neuron)
                self.hidden_layer = layer_neurons
            elif i == 2:
                for _ in range(self.layers[i]):
                    neuron = Neuron()
                    neuron.add_in_connections(self.hidden_layer)
                    neuron.add_bias_connection(self.bias)
                    layer_neurons.append(neuron)
                self.output_layer = layer_neurons

        for neuron in self.hidden_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                new_weight = self.get_random()
                connection.set_weight(new_weight)

        for neuron in self.output_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                new_weight = self.get_random()
                connection.set_weight(new_weight)

    def get_random(self):
        return self.random_weight_multiplier * (self.rand.random() * 2 - 1)
    
    def set_input(self, inputs):
        for i in range(len(self.input_layer)):
            self.input_layer[i].set_output(inputs[i])

    def get_output(self):
        outputs = []
        for neuron in self.output_layer:
            outputs.append(neuron.get_output())
        return outputs

    def activate(self):
        for neuron in self.hidden_layer:
            neuron.calculate_output()
        for neuron in self.output_layer:
            neuron.calculate_output()

    def apply_backpropagation(self, expected_output):
        for i, neuron in enumerate(self.output_layer):
            connections = neuron.get_all_in_connections()
            for connection in connections:
                ak = neuron.get_output()
                ai = connection.get_from_neuron().get_output()
                desired_output = expected_output[i]
                partial_derivative = -ak * (1 - ak) * ai * (desired_output - ak)
                delta_weight = -self.learning_rate * partial_derivative
                new_weight = connection.get_weight() + delta_weight
                connection.set_delta_weight(delta_weight)
                connection.set_weight(new_weight + self.momentum * connection.get_prev_delta_weight())

        for neuron in self.hidden_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                aj = neuron.get_output()
                ai = connection.get_from_neuron().get_output()
                sum_k_outputs = 0
                j = 0
                for out_neuron in self.output_layer:
                    wjk = out_neuron.get_connection(neuron.id).get_weight()
                    desired_output = expected_output[j]
                    ak = out_neuron.get_output()
                    j += 1
                    sum_k_outputs += -(desired_output - ak) * ak * (1 - ak) * wjk

                partial_derivative = aj * (1 - aj) * ai * sum_k_outputs
                delta_weight = -self.learning_rate * partial_derivative
                new_weight = connection.get_weight() + delta_weight
                connection.set_delta_weight(delta_weight)
                connection.set_weight(new_weight + self.momentum * connection.get_prev_delta_weight())

    def run(self, max_steps, min_error):
        error = 1.0
        i = 0

        while i < max_steps and error > min_error:
            error = 0.0

            for p in range(len(self.inputs)):
                self.set_input(self.inputs[p])
                self.activate()
                self.output = self.get_output()
                self.result_outputs[p] = self.output

                for j in range(len(self.expected_outputs[p])):
                    err = (self.output[j] - self.expected_outputs[p][j])**2
                    error += err

                self.apply_backpropagation(self.expected_outputs[p])

            i += 1

        self.print_result()
        print("SSE = ", error , " [<{}]".format(min_error))
        print("EPOCHS COUNT =", i, " [<{}]".format(max_runs), "\n")

        if i == max_steps:
            print("!ERROR training try again")
        else:
            pass  # Add code if needed for successful training

    def print_result(self):
        print("AND")
        for p in range(len(self.inputs)):
            print("Inputs:", end=" ")
            for x in range(len(self.inputs[p])):
                print(self.inputs[p][x], end=" ")
            print("Expected:", end=" ")
            for x in range(len(self.expected_outputs[p])):
                print(self.expected_outputs[p][x], end=" ")
            print("Actual:", end=" ")
            for x in range(len(self.result_outputs[p])):
                print(self.result_outputs[p][x], end=" ")
            print()
        print()

class NeuralNetwork_OR:
    def __init__(self, input_size, hidden_size, output_size):
        self.is_trained = False
        self.df = 0.0
        self.rand = random.Random()
        self.input_layer = []
        self.hidden_layer = []
        self.output_layer = []
        self.bias = Neuron()
        self.layers = [input_size, hidden_size, output_size]
        self.random_weight_multiplier = 1
        self.epsilon = 0.00000000001
        self.learning_rate = 0.9
        self.momentum = 0.7
        self.inputs = [[1, 1], [1, 0], [0, 1], [0, 0]]
        self.expected_outputs = [[1], [1], [1], [0]]
        self.result_outputs = [[-1], [-1], [-1], [-1]]
        self.output = None
        self.weight_update = {}

        self.initialize_neurons()

    def initialize_neurons(self):
        for i in range(len(self.layers)):
            layer_neurons = []
            if i == 0:
                layer_neurons = [Neuron() for _ in range(self.layers[i])]
                self.input_layer = layer_neurons
            elif i == 1:
                for _ in range(self.layers[i]):
                    neuron = Neuron()
                    neuron.add_in_connections(self.input_layer)
                    neuron.add_bias_connection(self.bias)
                    layer_neurons.append(neuron)
                self.hidden_layer = layer_neurons
            elif i == 2:
                for _ in range(self.layers[i]):
                    neuron = Neuron()
                    neuron.add_in_connections(self.hidden_layer)
                    neuron.add_bias_connection(self.bias)
                    layer_neurons.append(neuron)
                self.output_layer = layer_neurons

        for neuron in self.hidden_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                new_weight = self.get_random()
                connection.set_weight(new_weight)

        for neuron in self.output_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                new_weight = self.get_random()
                connection.set_weight(new_weight)

    def get_random(self):
        return self.random_weight_multiplier * (self.rand.random() * 2 - 1)
    
    def set_input(self, inputs):
        for i in range(len(self.input_layer)):
            self.input_layer[i].set_output(inputs[i])

    def get_output(self):
        outputs = []
        for neuron in self.output_layer:
            outputs.append(neuron.get_output())
        return outputs

    def activate(self):
        for neuron in self.hidden_layer:
            neuron.calculate_output()
        for neuron in self.output_layer:
            neuron.calculate_output()

    def apply_backpropagation(self, expected_output):
        for i, neuron in enumerate(self.output_layer):
            connections = neuron.get_all_in_connections()
            for connection in connections:
                ak = neuron.get_output()
                ai = connection.get_from_neuron().get_output()
                desired_output = expected_output[i]
                partial_derivative = -ak * (1 - ak) * ai * (desired_output - ak)
                delta_weight = -self.learning_rate * partial_derivative
                new_weight = connection.get_weight() + delta_weight
                connection.set_delta_weight(delta_weight)
                connection.set_weight(new_weight + self.momentum * connection.get_prev_delta_weight())

        for neuron in self.hidden_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                aj = neuron.get_output()
                ai = connection.get_from_neuron().get_output()
                sum_k_outputs = 0
                j = 0
                for out_neuron in self.output_layer:
                    wjk = out_neuron.get_connection(neuron.id).get_weight()
                    desired_output = expected_output[j]
                    ak = out_neuron.get_output()
                    j += 1
                    sum_k_outputs += -(desired_output - ak) * ak * (1 - ak) * wjk

                partial_derivative = aj * (1 - aj) * ai * sum_k_outputs
                delta_weight = -self.learning_rate * partial_derivative
                new_weight = connection.get_weight() + delta_weight
                connection.set_delta_weight(delta_weight)
                connection.set_weight(new_weight + self.momentum * connection.get_prev_delta_weight())

    def run(self, max_steps, min_error):
        error = 1.0
        i = 0

        while i < max_steps and error > min_error:
            error = 0.0

            for p in range(len(self.inputs)):
                self.set_input(self.inputs[p])
                self.activate()
                self.output = self.get_output()
                self.result_outputs[p] = self.output

                for j in range(len(self.expected_outputs[p])):
                    err = (self.output[j] - self.expected_outputs[p][j])**2
                    error += err

                self.apply_backpropagation(self.expected_outputs[p])

            i += 1

        self.print_result()
        print("SSE = ", error , " [<{}]".format(min_error))
        print("EPOCHS COUNT =", i, " [<{}]".format(max_runs), "\n")

        if i == max_steps:
            print("!ERROR training try again")
        else:
            pass  # Add code if needed for successful training

    def print_result(self):
        print("OR")
        for p in range(len(self.inputs)):
            print("Inputs:", end=" ")
            for x in range(len(self.inputs[p])):
                print(self.inputs[p][x], end=" ")
            print("Expected:", end=" ")
            for x in range(len(self.expected_outputs[p])):
                print(self.expected_outputs[p][x], end=" ")
            print("Actual:", end=" ")
            for x in range(len(self.result_outputs[p])):
                print(self.result_outputs[p][x], end=" ")
            print()
        print()


class NeuralNetwork_XOR:
    def __init__(self, input_size, hidden_size, output_size):
        self.is_trained = False
        self.df = 0.0
        self.rand = random.Random()
        self.input_layer = []
        self.hidden_layer = []
        self.output_layer = []
        self.bias = Neuron()
        self.layers = [input_size, hidden_size, output_size]
        self.random_weight_multiplier = 1
        self.epsilon = 0.00000000001
        self.learning_rate = 0.9
        self.momentum = 0.7
        self.inputs = [[1, 1], [1, 0], [0, 1], [0, 0]]
        self.expected_outputs = [[0], [1], [1], [0]]
        self.result_outputs = [[-1], [-1], [-1], [-1]]
        self.output = None
        self.weight_update = {}

        self.initialize_neurons()

    def initialize_neurons(self):
        for i in range(len(self.layers)):
            layer_neurons = []
            if i == 0:
                layer_neurons = [Neuron() for _ in range(self.layers[i])]
                self.input_layer = layer_neurons
            elif i == 1:
                for _ in range(self.layers[i]):
                    neuron = Neuron()
                    neuron.add_in_connections(self.input_layer)
                    neuron.add_bias_connection(self.bias)
                    layer_neurons.append(neuron)
                self.hidden_layer = layer_neurons
            elif i == 2:
                for _ in range(self.layers[i]):
                    neuron = Neuron()
                    neuron.add_in_connections(self.hidden_layer)
                    neuron.add_bias_connection(self.bias)
                    layer_neurons.append(neuron)
                self.output_layer = layer_neurons

        for neuron in self.hidden_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                new_weight = self.get_random()
                connection.set_weight(new_weight)

        for neuron in self.output_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                new_weight = self.get_random()
                connection.set_weight(new_weight)

    def get_random(self):
        return self.random_weight_multiplier * (self.rand.random() * 2 - 1)
    
    def set_input(self, inputs):
        for i in range(len(self.input_layer)):
            self.input_layer[i].set_output(inputs[i])

    def get_output(self):
        outputs = []
        for neuron in self.output_layer:
            outputs.append(neuron.get_output())
        return outputs

    def activate(self):
        for neuron in self.hidden_layer:
            neuron.calculate_output()
        for neuron in self.output_layer:
            neuron.calculate_output()

    def apply_backpropagation(self, expected_output):
        for i, neuron in enumerate(self.output_layer):
            connections = neuron.get_all_in_connections()
            for connection in connections:
                ak = neuron.get_output()
                ai = connection.get_from_neuron().get_output()
                desired_output = expected_output[i]
                partial_derivative = -ak * (1 - ak) * ai * (desired_output - ak)
                delta_weight = -self.learning_rate * partial_derivative
                new_weight = connection.get_weight() + delta_weight
                connection.set_delta_weight(delta_weight)
                connection.set_weight(new_weight + self.momentum * connection.get_prev_delta_weight())

        for neuron in self.hidden_layer:
            connections = neuron.get_all_in_connections()
            for connection in connections:
                aj = neuron.get_output()
                ai = connection.get_from_neuron().get_output()
                sum_k_outputs = 0
                j = 0
                for out_neuron in self.output_layer:
                    wjk = out_neuron.get_connection(neuron.id).get_weight()
                    desired_output = expected_output[j]
                    ak = out_neuron.get_output()
                    j += 1
                    sum_k_outputs += -(desired_output - ak) * ak * (1 - ak) * wjk

                partial_derivative = aj * (1 - aj) * ai * sum_k_outputs
                delta_weight = -self.learning_rate * partial_derivative
                new_weight = connection.get_weight() + delta_weight
                connection.set_delta_weight(delta_weight)
                connection.set_weight(new_weight + self.momentum * connection.get_prev_delta_weight())

    def run(self, max_steps, min_error):
        error = 1.0
        i = 0

        while i < max_steps and error > min_error:
            error = 0.0

            for p in range(len(self.inputs)):
                self.set_input(self.inputs[p])
                self.activate()
                self.output = self.get_output()
                self.result_outputs[p] = self.output

                for j in range(len(self.expected_outputs[p])):
                    err = (self.output[j] - self.expected_outputs[p][j])**2
                    error += err

                self.apply_backpropagation(self.expected_outputs[p])

            i += 1

        self.print_result()
        print("SSE = ", error , " [<{}]".format(min_error))
        print("EPOCHS COUNT =", i, " [<{}]".format(max_runs), "\n")

        if i == max_steps:
            print("!ERROR training try again")
        else:
            pass  # Add code if needed for successful training

    def print_result(self):
        print("XOR")
        for p in range(len(self.inputs)):
            print("Inputs:", end=" ")
            for x in range(len(self.inputs[p])):
                print(self.inputs[p][x], end=" ")
            print("Expected:", end=" ")
            for x in range(len(self.expected_outputs[p])):
                print(self.expected_outputs[p][x], end=" ")
            print("Actual:", end=" ")
            for x in range(len(self.result_outputs[p])):
                print(self.result_outputs[p][x], end=" ")
            print()
        print()


if __name__ == "__main__":
    nn_and = NeuralNetwork_AND(2, 4, 1)
    max_runs = 50000
    min_error_condition = 0.001
    nn_and.run(max_runs, min_error_condition)



    nn_or = NeuralNetwork_OR(2, 4, 1)
    max_runs = 50000
    min_error_condition = 0.001
    nn_or.run(max_runs, min_error_condition)


    nn_xor = NeuralNetwork_XOR(2, 4, 1)
    max_runs = 50000
    min_error_condition = 0.001
    nn_xor.run(max_runs, min_error_condition)
