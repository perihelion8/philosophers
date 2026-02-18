_This project has been created as part of the 42 curriculum by abazzoun._

# Philosophers

## Description

The Philosophers project is a concurrency and synchronization challenge based on the classic Dining Philosophers problem. This project strengthens understanding of concurrent programming and low-level system behavior.

## Instructions

### Compile 

To compile: `make`

### Run

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- number_of_philosophers: number of philosophers (and forks)
- time_to_die: time in milliseconds before a philosopher dies if they don’t eat
- time_to_eat: time in milliseconds a philosopher spends eating
- time_to_sleep: time in milliseconds a philosopher spends sleeping
- [number_of_times_each_philosopher_must_eat]: optional argument; simulation stops when all philosophers have eaten this many times

## Resources

- Operating Systems: Three Easy Pieces
- Manual Pages
- AI used for debugging sometimes