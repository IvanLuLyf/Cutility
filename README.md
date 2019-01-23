# Cutility

## Usage

## Lambda Expression

```C
int c = lambda(int, (int a,int b){ return a+b; })(1,2); // get c = 3
```

or

```C
int (*func)(int,int) = lambda(int, (int a,int b){ return a+b; }); // get function pointer
int c = func(1,2); // get c = 3
```

## ArrayList

### Initial

```C
ArrayList *list = InitArrayList(50); // Capacity of ArrayList
```

or

```C
ArrayList *list = InitArrayList(); // Default Capacity is 10
```

### Insert

```C

ArrayListInsert(list, 0, IntVal(1)); // Insert in specified position

ArrayListInsertMany(list, 2, IntVal(1), IntVal(2)); // Insert some variables

ArrayListAppend(list, IntVal(10)); // Insert into back of list
```


