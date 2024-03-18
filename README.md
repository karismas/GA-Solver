# Genetic Algorithm Solver

This is some code I wrote when I was 16. I had heard about something called "genetic algorithms" and thought they sounded super neat. I wanted to try my hand at using it to make a little game, so here it is.

___

## How It Works

The genetic algorithm works as follows:

- The user specifies a set of genes (as a string), number of generations, and number of organisms.
- The amount of organisms that the user specified are created with randomized genes.
- Each organism gets a calculation of its "fitness score". This is just the unsigned ASCII value distance from the correct letter to the current organism's letter.
- The two best organisms are selected to breed, and they produce two offspring with genes that were creating from splicing the parent genes at a random point. This is repeated for the next best two organisms, and the next, and so on.
- Once that generation has finished, the next generations repeat this process.
- If the desired set of genes are reached, the program terminates early. Otherwise, it keeps running until the number of generations specified by the user are exhausted.

___

## How To Play

Playing is pretty easy. The game will first prompt you with:

> Welcome to the Genetic Algorithm phrase guesser!
>
> What phrase would you like the algorithm to guess?
>
> \>

You can put in any collection of words or ASCII characters you'd like, but try not to make it too long! (it will take a long time otherwise) I'd try to keep it between 1 - 30 characters.

After your input, the next prompt will be:

> How many organisms would you like in the population? (must be an even number)
>
> \>

This number should be based on how many characters you put in your phrase, since you'll need diversity in genes to eventually reach your prompt. I'd start with ~1000 for smaller stuff (<10 characters). Anything higher and you'll have to start increasing it. Experiment!

After this, the next prompt is:

> How many generations would you like to run?
>
> \>

Again, this is dependent on how difficult your prompt is. I'd start at around 100 for smaller stuff and increase it for anything more difficult than that.

The last prompt you'll get is:

> Would you like to print:
>
> (a) All organisms for each generation.
> 
> (b) Only the best organism for each generation.
> 
> Choose (a/b).
>
> \>

The prompt is pretty self-explanatory. Option `a` is really cool to watch because you get to see the diversity in genes, although it will take longer since so much printing has to happen. Option `b` is faster and also cool since you get to see how the best organism from each generation is slowly approaching the desired genes.

After submitting the final option, you should see the 

___

## To Do

- The main component that this program is missing is mutations. Mutations are very important in how much genes vary, and I've seen quite a few instances of this program getting stuck right before reaching the goal. Adding mutations would allow the algorithm to "get out of the hole", so to speak.
- Since I wrote this when I had no understanding of data structures and algorithmic complexity, it's riddled with inefficient code. I'm sure I could speed it up by quite a large margin.
- There are other edge cases, like entering nothing into the prompts, causing `stoi` to freak out. I'll fix that later (I probably won't).
