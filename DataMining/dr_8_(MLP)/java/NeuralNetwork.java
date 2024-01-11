import java.text.*;

public class NeuralNetwork {
    static{
        Locale.setDefault(Locale.ENGLISH);
    }
    final boolean isTrained= false;
    final DecimalFormat df;
    final Random rand = new Random();
    final ArrayList<Neuron> inputLayer = new ArrayList<Neuron>();
    final ArrayList<Neuron> hiddenLayer = new ArrayList<Neuron>();
    final ArrayList<Neuron> outputLayer = new ArrayList<Neuron>();
    final Neuron bias = new Neuron();
    final int[] layers;
    final int randomWeightMultiplier = 1;
    

    final double epsilon = 0.00000000001;
    final double learningRate = 0.9f;
    final double momentum = 0.7f;

    //inputs for xor problem
    final double inputs[][] = {{1,1},{1,0},{0,1},{0,0}};

    //outputs for xor problem
    final double expectedOutputs[][] = { {0}, {1} , {1} , {0}};
    double resultOutputs [][] = {{-1}, {-1}, {-1}, {-1}};
    double output[];

    //for weight update all 
    final HashMap<String, Double> weightUpdate = new HashMap<String,Double>();

    public static void main(String[] args) {
        NeuralNetwork nn = new NeuralNetwork (2,4,1);
        int maxRuns= 50000;
        double minErrorCondition = 0.001;
        nn.run(maxRuns,minErrorCondition);
    }
    public NeuralNetwork(int input, int hidden, int output) {
        this.layers = new input[] {input,hidden,output};
        df = new DecimalFormat("#.0#");

        /*
            Create all neurons and connections , connections are created in the neuron class
        */
        for(int i=0; i< layers.length; i++)
        {
            if(i==0)
            {
                for(int j=0; j<layers[i]; j++)
                {
                    Neuron neuron = new Neuron();
                    inputLayer.add(neuron);
                }
            }
            else if (i==1)
            {
                 for(int j=0; j<layers[i]; j++)
                {
                    Neuron neuron = new Neuron();
                    neuron.addInConnectionsS(inputLayer);
                    neuron.addBiasConnection(bias);
                    hiddenLayer.add(neuron);
                }
            }
            else if (i==2)
            {
                for(int j=0; j< layers[i]; j++)
                {
                    Neuron neuron= new Neuron();
                    neuron.addInConnectionsS(hiddenLayer);
                    neuron.addBiasConnection(bias);
                    outputLayer.add(neuron);
                }
            }    
            else {
                System.out.println("!Error in NeuralNetwork init");
            }
        }
        for(Neuron neuron: hiddenLayer)
        {
            ArrayList<Connection> connections = neuron.getAllInConnections();
            for(Connection conn: connections)
            {
                double newWeight= getRandom();
                conn.setWeight(newWeight);
            }
        }
        for(Neuron neuron: outputLayer)
        {
            ArrayList<Connection> connections = neuron.getAllInConnections();
            for(Connection conn: connections)
            {
                double newWeight= getRandom();
                conn.setWeight(newWeight);
            }
        }
        //reset id counters
        Neuron.counter=0;
        Connection.counter=0;

        // if(isTrained)
        // {
        //     trainedWeights();
        //     updateAllWeights();
        // }
    }

    //random 
    double getRandom()
    {
        return randomWeightMultiplier * (rand.nextDouble() * 2 - 1); // [-1;1]
    }
    public void setInput(double inputs[]) {
        for(int i=0; i<inputLayer.size();i++)
        {
            inputLayer.get(i).setOutput(inputs[i]);
        }
    }
    public double[] getOutput()
    {
        double[] outputs = new double [outputLayer.size()];
        for (int i=0; i<outputLayer.size();i++){
            outputs[i]= outputLayer.get(i).getOutput();
        }
        return outputs;
    }

    /**
     * Calculate the output of the neural network based on the input . The forward operation
     */

    public void activate()
    {
        for (Neuron n : hiddenLayer)
        {
            n.calculateOutput();
        }
        for (Neuron n: outputLayer)
        {
            n.calculateOutput();
        }
    }

    /**
     * all output propagate back
     * @param expectedOutput
     *        first calculate the partial derivative of the error with respect
     *        to each of the weight leading into the output neurons
     *        bias is also updated here 
     * 
     */
    public void applyBackpropagation(double expectedOutput[])
    {
        //error check ,normalize value [0;1]
        for(int i=0; i<expectedOutput.length; i++)
        {
            double d = expectedOutput[i];
            if(d<0 || d > 1)
            {
                if(d<0)
                {
                    expectedOutput= 0 + epsilon;
                }
                else
                {
                    expectedOutput= 1 - epsilon;
                }
            }
        }
        int i=0;

        //update weights for the output layer
        for(Neuron n : outputLayer)
        {
            ArrayList<Connection> connections = n.getAllInConnections();
            for(Connection con: connections)
            {
                double ak= n.getOutput();
                double ai = con.leftNeuron.getOutput();
                double desiredOutput= expectedOutput[i];
                double partialDerivative= -ak * (1-ak) * ai * (desiredOutput - ak);
                double deltaWeight=-learningRate *partialDerivative;
                double newWeight= con.getWeight() + deltaWeight;
                con.setDeltaWeight(deltaWeight);
                con.setWeight(newWeight+momentum*con.getPrevDeltaWeight());
            }
            i++;
        }

        //update weights for the hidden layer
        for(Neuron n: hiddenLayer)
        {
            ArrayList<Connection> connections = n.getAllInConnections();
            for(Connection con: connections)
            {
                double aj= n.getOutput();
                double ai = con.leftNeuron.getOutput();
                double sumKoutputs = 0;
                int j = 0;
                for(Neuron out_new: outputLayer)
                {
                    double wjk = out_new.getConnection(n.id).getWeight();
                    double desiredOutput = (double) expectedOutput[j];
                    double ak= out_new.getOutput();
                    j++;
                    sumKoutputs= sumKoutputs + (-(desiredOutput - ak) * ak * (1-ak) * wjk);
                }
                double partialDerivative= aj * (1-aj) * ai * sumKoutputs;
                double deltaWeight= -learningRate * partialDerivative;
                double newWeight= con.getWeight() + deltaWeight;
                con.setDeltaWeight(deltaWeight);
                con.setWeight(newWeight+ momentum * con.getPrevDeltaWeight());
            }

        }

    }

    void run (int maxSteps, double minError)
    {
        int i;
        //Train neural network until minError reached or maxSteps exceeded
        double error = 1;
        for(i = 0 ; i< maxSteps && error > minError ; i++)
        {
            error=0;
            for(int p = 0 ; p <inputs.length ; p++)
            {
                setInput(inputs[p]);
                activate();
                output = getOutput();
                resultOutputs[p] = output;

                for(int j = 0 ; j < expectedOutputs[p].length; j++)
                {
                    double err = Math.pow((output[j]-expectedOutputs[p][j]),2);
                    error+=err;
                }
                applyBackpropagation(expectedOutputs[p]);
            }
        }
        printResult();
        System.out.println("Sum of squared errors = " + error);
        System.out.println("#### EPOCH = " + i + "\n");
        if(i==maxSteps)
        {
            System.out.println("!ERROR training try again");
        }
        else{
            // printAllWeights();
            // printWeightUpdate();
        }
    }
    void printResult()
    {
        System.out.println("NN example with xor training");
        for(int p=0; p < inputs.length ; p++)
        {
            System.out.print("Inputs: ");
            for(int x = 0; x <layers[0]; x++)
            {
                System.out.print(inputs[p][x] + " ");
            }

            System.out.print("Expected: ");
            for(int x = 0; x <layers[2]; x++)
            {
                System.out.print(expectedOutputs[p][x] + " ");
            }

            System.out.print("Actual: ");
            for(int x = 0; x <layers[2]; x++)
            {
                System.out.print(resultOutputs[p][x] + " ");
            }
            System.out.println();
        }

        System.out.println();

    }
    // String weightKey(int neuronId, int conId)
    // {
    //     return "N" + neuronId + "_C"+conId;
    // }

    // public void updateAllWeights()
    // {
    //     for(Neuron n: outputLayer){
    //         ArrayList<Connection> connections = n.getAllInConnections();
    //         for(Connection con : connections){
    //             String key = weightKey(n.id, con.id);
    //             double newWeight = weightUpdate.get(key);
    //             con.setWeight(newWeight);
    //         }
    //     }
    //     for(Neuron n: hiddenLayer){
    //         ArrayList<Connection> connections = n.getAllInConnections();
    //         for(Connection con : connections){
    //             String key = weightKey(n.id, con.id);
    //             double newWeight = weightUpdate.get(key);
    //             con.setWeight(newWeight);
    //         }
    //     }
    // }
    // void trainedWeights()
    // {
    //     weightUpdate.clear();
    //     weightUpdate.put(weightKey(3,0), 1.03)
    // }

}



