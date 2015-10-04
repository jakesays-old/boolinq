# Introduction #

Using `.where()` method you can filter any source range.

# Details #

It have single parameter, witch is lambda, those shouuld return bool for each element of source range.

# Examples #

Example of filtering {0,1,2,3,4,5,6,7,8,9} to {3,5,7}

```
int vec[] = {0,1,2,3,4,5,6,7,8,9};
auto dst = boolinq::from(vec).where([](int a){return a <= 7;}) // 0,1,2,3,4,5,6,7
                             .where([](int a){return a >= 2;}) // 2,3,4,5,6,7
                             .where([](int a){return a%2==1;}) // 3,5,7
                             .toVector();
```