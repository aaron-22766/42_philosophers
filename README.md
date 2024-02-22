<h1 align="center">
	<p>
	philosophers
	</p>
	<img src="https://github.com/aaron-22766/aaron-22766/blob/main/42-badges/philosopherse.png">
</h1>

<p align="center">
	<b><i>I never thought philosophy would be so deadly</i></b><br><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/aaron-22766/42_philosophers?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/aaron-22766/42_philosophers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/aaron-22766/42_philosophers?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/aaron-22766/42_philosophers?color=green" />
</p>

---

## 🗣 About

Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger. You will learn the basics of threading a process, how to create threads and work with mutexes.

## 🛠 Usage

```shell
$> cd philo
$> make
$> ./philo [philos] [die time] [eat time] [sleep time] [eat limit (optional)]
```

## 💬 Description

### The Dining Philosophers problem

* One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
* There are also forks on the table. There are as many forks as philosophers.
* Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
* Every philosopher needs to eat and should never starve.
* Philosophers don’t speak with each other.
* Philosophers don’t know if another philosopher is about to die.
* No need to say that philosophers should avoid dying!
* Your program must ot have any data races!

![Dining Philosophers](https://github.com/aaron-22766/aaron-22766/blob/main/bin/images/Dining%20Philosophers.png)

## ⭐️ My approach

* Each fork is a mutex, which get created first
* Philos are initialized with each having a pointer to their left ad right fork
* They also have mutexes that protect their `eat_count` and `time_last_eaten` variables, which is important since those are monitored by the seperate monitor threads
* Current time is saved as the start time for the simulation
* The philo threads are created followed by the death and eat limit monitor threads
* Each philo will run the same routine:
	- checks if it's only one philo, in which case he only takes the only fork and then dies
 	- a time delay of 50µs for each odd id of the philo
  	- while the `exit` variable, which is set by the monitor threads, is false the following steps get repeated
  	- takes forks (locks mutexes), even philos from left to right, odd ones from right to left (this prevents them all taking just the left which leads to a dead lock)
  	- `time_last_eaten` is set to the current time
  	- waits the amount of `eat time`
  	- puts the forks back on the table (unlocks mutexes)
  	- `eat_count` is incremented
  	- waits the amount of `sleep time`
  	- then thinks and tries to take forks again
 * The death monitor thread just checks the `time_last_eaten` of each philo and if it's bigger than `die time` it sets the `exit` variable true
 * The eat limit monitor does the same with the `eat limit` if it was specified

During the entire program the philos print what they are doing like this:
```shell
$> ./philo 2 500 200 200 3
0 2 has taken a fork
1 2 has taken a fork
1 2 is eating
201 2 is sleeping
201 1 has taken a fork
201 1 has taken a fork
201 1 is eating
401 1 is sleeping
401 2 is thinking
401 2 has taken a fork
401 2 has taken a fork
401 2 is eating
601 2 is sleeping
601 1 is thinking
601 1 has taken a fork
601 1 has taken a fork
601 1 is eating
801 1 is sleeping
801 2 is thinking
801 2 has taken a fork
801 2 has taken a fork
801 2 is eating
1001 1 is thinking
1001 2 is sleeping
1001 1 has taken a fork
1001 1 has taken a fork
1001 1 is eating
1201 2 is thinking
1201 1 is sleeping
```
[This really cool website](https://nafuka11.github.io/philosophers-visualizer/) lets you visualize the simulation, just copy paste the output.


