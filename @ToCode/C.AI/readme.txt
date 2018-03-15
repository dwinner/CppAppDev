About the CD-ROM

The CD-ROM contains a number of useful applications that demonstrate 
the properties of AI algorithmic techniques and methods. The methods 
and applications that demonstrate them are noted in this section.

Simulated Annealing
Simulated annealing, or modeling of systematic cooling of a molten 
metal to a solid, is described in Chapter 2. The theoretical N-Queens 
problem is used to demonstrate the constraint satisfaction properties 
of the algorithm. The algorithm and application can be found on the 
CD-ROM at ./software/ch2.

Adaptive Resonance Theory
Adaptive Resonance Theory, also called ART-1, is a clustering algorithm 
that provides the ability to separate (or cluster) elements in a data 
set into independent data sets based upon properties of the individual 
data items. The algorithm does this in an unsupervised manner, allowing 
the algorithm to find patterns in the data that a user may not notice. 
The practical problem of personalization is used to demonstrate ART1 
in the context of a recommender  system in Chapter 3. The algorithm and 
application can be found on the CD-ROM at ./software/ch3.

Ant Algorithms
Ant algorithms are a relatively new method that can be used to identify 
optimal paths through a graph. This method is described in Chapter 4. 
Ant algorithms model the movement of ants within an environment and use 
simulated pheromone  to communicate with other ants (the process of 
stigmergy). The theoretical problem of the Traveling Salesman Problem 
(or TSP) is used to demonstrate the ant algorithm. The algorithm and 
application can be found on the CD-ROM at ./software/ch4.

Backpropagation Algorithm
The backpropagation algorithm, discussed in Chapter 5, is one of the 
primary methods used to train multi-layer neural networks given a 
training set and a set of desired outputs.  Backpropagation propagates 
errors back through the nodes of a network, altering the weights of the 
connections based upon the error of the actual and desired outputs.  The 
interesting problem of training game neurocontrollers (game AI) is used 
to demonstrate backpropagation. Given a simple neural network, a set 
of environmental inputs and a set of allowable actions (otherwise known 
as the training set), the algorithm trains the network to perform the 
desired action for the current environment. It is then demonstrated 
that the neurocontroller is able to generalize and perform useful 
behaviors for unforeseen environments. The backpropagation algorithm 
and neurocontroller application can be found on the CD-ROM at 
./software/ch5.

Genetic Algorithms / Genetic Programming
Genetic algorithms provide a novel optimization technique that can 
be applied to both numerical and symbolic problems, and is described 
in Chapter 6. The subfield of Genetic programming is further used to 
illustrate the creation of instruction sequences to solve problems 
in code generation. Sequences of instructions are evolved to solve 
mathematical functions, and it is demonstrated how these sequences 
can find novel strings that are both interesting and optimal given a 
simple virtual machine. The genetic programming algorithm and 
application can be found on the CD-ROM at ./software/ch6.

Artificial Life / Evolving Neural Networks
Artificial life is studied here in the context of neural networks 
through evolution of simple organisms in a synthetic environment and 
is described in Chapter 7. Organisms survive through successfully 
existing within their environment, avoiding prey and foraging for 
food. Organisms are permitted to reproduce, once they reach a high 
enough level of internal energy. Therefore, reproduction is only 
permitted if organisms can survive within the environment, which 
should lead to more fit organisms. The organisms are provided with 
multi-layer neural networks as their neurocontrollers, and given two 
different types of organisms, illustrate simple food-web organizations. 
The artificial life application can be found on the CD-ROM at 
./software/ch7.

Expert Systems
Rules-based systems are the topic of Chapter 8, which emphasis and 
implementation of a forward-chaining system. Varieties of examples 
are provided, in the form of rules and initial facts, with a final 
example of embedded the rules-based system into an embedded system 
and utilizing it for sensor fault-tolerance. The forward-chaining 
rules-based system and application files can be found on the CD-ROM 
at ./software/ch8.

Fuzzy Logic
In Chapter 9, fuzzy logic and fuzzy control are described including 
an implementation of a fuzzy API for inclusion into other applications. 
The API provides not only the standard fuzzy operators, but also helper 
functions that support the simple creation of fuzzy membership 
functions. The fuzzy logic API and a simple battery charger example 
is provided on the CD-ROM at ./software/ch9.

Hidden Markov Models
Hidden Markov models are the topic of Chapter 10, which are networks 
that include states and transitions with associated probabilities. The 
outcome, or observation, of a state is generated based upon the 
associated probability distribution. The action is performed, made 
visible, though the internal state is hidden, thus the hidden aspect of 
the Markov model. Hidden Markov models have a variety of applications; 
in Chapter 10 we look at the generation of meaningful text based upon 
training by a corpus. The HMM and a text generation example is provided 
on the CD-ROM at ./software/ch10.


Intelligent Agents
Intelligent agents are the final topic in Chapter 11, with emphasis 
on search and filtering agents. Intelligent agents are applied in a 
number of different ways; the application chosen for this chapter is a 
filtering agent that acts as an intermediary to UseNet sites on the 
Internet. The WebAgent is configured through a simple configuration 
file. It then autonomously gathers news using the NNTP protocol and 
presents it to the user with the HTTP protocol (acting as a simple web 
server). The WebAgent is provided on the CD-ROM at ./software/ch11.

System Requirements
Applications on this CD-ROM require a PC with Windows 95, 98, 2000, 
Me, or XP using the Cygwin UNIX environment (freely downloadable at 
www.cygwin.com), or Linux (Red Hat 6.1 or later, or comparable Linux 
distribution); 486 or higher CPU; 64MB RAM; 60MB disk space; CD-ROM 
drive; Internet access and Web browser (for the WebAgent example).

