# TM
TM was created in 2014. as a project for a course in discrete mathematics. It's a C implementation of a [Turing machine](https://en.wikipedia.org/wiki/Turing_machine#Formal_definition)
with the visuals and animation done in the same way as in [Zmija](../../../Zmija).

### Menu - tape input
<details><summary>[see the first menu]</summary>
<p>

The first menu presents options for inputting the tape:

`1` through the console

`2` through a text file

`3` prints the input format
<details><summary>[see output]</summary>
<p>

'b' is used as the blank symbol, spaces and new lines are ignored

</p>
</details>
<br>

`0` quit the application

</p>
</details>

### Menu - program input
<details><summary>[see the second menu]</summary>
<p>

After the tape has been entered the second menu prompts you to chose the program input method:

`1` through a text file
<details><summary>[Example program]</summary>
<p>

A program that checks if a binary number is divisible by 4:

```
f(q0,1)->(q1,1,+1)

f(q1,0)->(q1,0,+1)
f(q1,1)->(q1,1,+1)
f(q1,b)->(q2,b,-1)

f(q2,0)->(q3,0,-1)
f(q2,1)->(q-,1,+1)
f(q3,0)->(q+,0,+1)
f(q3,1)->(q-,1,+1)
```

</p>
</details>
<br>

`2` chose an existing program
<details><summary>[see output]</summary>
<p>

Option `5` expects a binary number but all the other options expect unary numbers
where zero is represented as '1', one as '11', two as '111' and so on.
Options `3` and `4` expect two numbers separated by '0'.
- `1` zero function
- `2` [successor](https://en.wikipedia.org/wiki/Successor_function)
- `3` first [projection](https://en.wikipedia.org/wiki/Projection_(set_theory))
- `4` sum
- `5` divisibility by 4
- `0` quit the application

</p>
</details>
<br>

`3` prints the input format
<details><summary>[see output]</summary>
<p>

- spaces and new lines are ignored
- f(q<sub>i</sub>,a<sub>i</sub>) -> (q<sub>j</sub>,a<sub>j</sub>,r)
  * q - internal state
  * a - tape alphabet symbol
  * r - head shift direction (+1 or -1)
  * i = {0, 1, ..., n}
  * j = {0, 1, ..., n, +, -}

</p>
</details>
<br>

`0` quit the application

</p>
</details>

### Controls
<details><summary>[see the controls]</summary>
<p>

Once both the tape and the program have been entered the Turing machine will be displayed.
The step counter and current state are displayed in the bottom right corner.

`v` and `b` can be used to move the view of the tape.
`k` runs one step of the Turing machine while and `s` and `z` start and stop a automatic run.
`Esc` quits the application.

</p>
</details>

### How it looks:
![](assets/img/TM.gif?raw=true)

Prove that C is Turing complete: :ballot_box_with_check:
