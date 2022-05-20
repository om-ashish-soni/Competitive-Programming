
# Competitive-Programming
## tips:
### 1. stuck in contest :
       take 1 or 2 min break, wash face and start again with freshness
### 2. can't improve :
       try to upsolve, no idea comming see editorial and if un-none topic learn it, repeat this
### 3. how to boost performance:
       always and almost long challanges on codechef helps to boost performance and learn various tips and techniques
### 4. how to combine different approach and solve problem : 
       let's say there is a problem and you performed below steps
       1. the problem is of graph , dfs -> not enought to solve a problem ?
       2. using disjoint set -> yes -> but tle
       3. using path compression -> yes -> but wrong answer on some edge case
       4. oh , look at the constraints , can we use fenwick tree? yes -> Solved -> AC
       these are the steps that how to combine different approaches
### 5. Can not solve last 3 to 4 problem of contest :
       If your basics are clear , then you need to practise a lot of problems of tree,graph,dp, segment trees,
       until you feel satisfied enough
### 6. Where and how to practise :
       1.always hackerrank is good to learn a language for beginners
       2. after having little grip on 1 language, go to codeforces problem set
       3. on codeforces problem set solve problem of rating < 1000
       4. solve topic wise problem on codeforces problem set
       5. give contest on codeforces and codechef
       6. upsolve problems , if can not solve in 30 mins , see editorial, if unnone topic , learn it, and repeat this
       7. after rating growth, repeat  step-4 and solve problems of rating range [your rating -100 , your rating + 100]
       8. keep learning new algo and practice them
### 7. How problem setters every time finds and puts new problem in contest : 
       see , its not that every problem was built from scratch , 
       most of the problems in contests are mixture of more than one problem of below cses sheet.
       
### CSES SHEET : [cses sheet](https://cses.fi/problemset/)
       
### 8. Which ide should i use ?
       Don't use ide in competitive programming , make a habit of using vim editor.
       
### vim-configuration
       set number
       set tabstop=4
       set shiftwidth=4
       set autoindent
       set mouse=a
       colorscheme default
       autocmd vimEnter *.cpp map ^B :w <CR> :!clear ; g++ --std=c++17 %;if[[-f Output : ++++++++++++++++++++++++++++++++] a.out ];time ./a.out; rm a.out; if[[-f End : --------------------------------]a.out]<CR>
  
### Note : 

  ### do below commands : 
  
      vi ~/.vimrc

      //then write above code of vim-configuration

      press ctrl-c and then ctrl-b to compile and run the code
  
### vim is the one of the best suitable editor for competitive programming in the world.
  
### 9. Which template should i use in cp?
       Oops , there are two much templates, look below reference.
       
###[templates useful for cp](https://iq.opengenus.org/cpp-template-for-competitive-coding/)
       
## codechef Roadmap
  1. start with array -> practice -> 2 🌟
  2. learn c++ stl or any language similar library, dp -> 3 🌟
  3. disjoint set union , graph, little dsa -> 4 🌟
  4. segment tree -> 5 🌟

## python jump by 2
```python:
for i in range(0,10,2):
  print(i)
```
## You might not know this 
https://www.geeksforgeeks.org/heap-using-stl-c/

## how to avoid recursion depth problem in python : 
sys.setrecursionlimit(10 ** 6)
## C++ tricks : 
https://codeforces.com/blog/entry/15643

## roadmap : 
https://blog.shahjalalshohag.com/topic-list/

## cf blogs : 
https://codeforces.com/catalog

## note to me:

* number theory , bit manip and dp are most popular, 
* in 98% of the contest atleast one of them is always there,
* please practise more and more

Some basic constraints and the safe time complexity :
---
| N | Big Oh |
|-----|------|
|For N <= 10 | O(2^N) and O(N!)|
|For N <= 100 | O(N^3) |
|For N <= 10^3 | O(N^2) |
|For N <=10^5 | O(NLogN) [ Sorting/Greedy Algo] |
|For N <= 10^6 | O(N) |
|For N <= 10^9 | O(logN) |

---
# nice youtube channels : 
|channel|
|-------|
|[Tushar Roy](https://www.youtube.com/channel/UCZLJf_R2sWyUtXSKiKlyvAw)|
|[Striver](https://www.youtube.com/channel/UCJskGeByzRRSvmOyZOz61ig)|
|[CodeNCode](https://www.youtube.com/channel/UC0zvY3yIBQTrSutsV-4yscQ)|
|[Tech-Dose](https://www.youtube.com/channel/UCnxhETjJtTPs37hOZ7vQ88g)|
|[Luv](https://www.youtube.com/channel/UCDzhFuVYou1D8w1ABZo3b9A)|
|[Apna college Placement course](https://www.youtube.com/playlist?list=PLfqMhTWNBTe0b2nM6JHVCnAkhQRGiZMSJ)|
|[Errichto](https://www.youtube.com/channel/UCBr_Fu6q9iHYQCh13jmpbrg)|


# Other nice repos : 
| repo |
|------|
|[Tourist](https://github.com/the-tourist/algo)|
|[dhiraj-01 CP](https://github.com/dhiraj-01/CP)|
|[Ashish Gupta](https://github.com/Ashishgup1/Competitive-Coding)|
|[Leetcode questions](https://github.com/fterh/leetcode-curation-topical)|
|[Algo-lib](https://github.com/saketh-are/algo-lib)|
|[Coding notes](https://github.com/ankitpriyarup/Coding_Notes)|
|[Atcoder library](https://github.com/atcoder/ac-library)|
|[Alexandru Valeanu](https://github.com/AlexandruValeanu/Competitive-Programming)|

---

# important topic reference 

|topic ref link|
|--------------|
|[Dynamic programming](https://youtu.be/oBt53YbR9Kk)|
|[Maths for dsa & cp](https://www.youtube.com/watch?v=tDM6lT-qjys)|

---
# nice articles 
|article ref link|
|----------------|
|[Roadmap for cp](https://www.geeksforgeeks.org/competitive-programming-a-complete-guide/)|
|[modulo multiplicative inverse](https://www.geeksforgeeks.org/modular-multiplicative-inverse-1-n/)|
---
# Important links : 
https://leetcode-questions.herokuapp.com/

# Problem sheet : 
https://cses.fi/problemset/

# contest : 
https://clist.by/

---
## good to know
- at max a number can have O(2*sqrt(n)-1) factors , which number of factors' upper bound .
- A leaf node is a node with degree less than or equal to 1.
---
# Roadmap

---
## number theory and combinatorics
| topic | ref link |
| ----- |----------|
|prime number||

---
| topic | ref link |
| ----- |----------|




