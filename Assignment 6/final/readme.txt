Issues ran into
I accidentaly created a race condition by passing variable that indicate which
number of thread that the function is running. I did some test and realized that
I need to create seperate variable for each thread so I created a thread_id
array.

Performance Discussion
I seems that my inplementation is very effective considering the time it take to 
run the test
the single thread take
real    0m42.059s
user    0m42.053s
sys     0m0.000s

two threads take
real    0m21.813s
user    0m43.448s
sys     0m0.001s

four threads take
real    0m11.192s
user    0m44.458s
sys     0m0.001s

eight threads take
real    0m5.763s
user    0m44.624s
sys     0m0.003s

the time almost halfed every time the thread is doubled
