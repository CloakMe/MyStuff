import math

def Fib(n):
    f_n = ( math.pow( ((1+math.sqrt(5))/2), n) - math.pow( ((1-math.sqrt(5))/2), n) )/math.sqrt(5)
    return f_n

def solve(y):

    eps = 1e-6

    test_n = math.log( math.sqrt(5)*y, (1+math.sqrt(5))/2)
    print(test_n)

    n = math.ceil(test_n)

    f_n = Fib(n-1)
    if( abs(f_n - y) < eps ):
        return 'IsFibo'
    f_n = Fib(n)
    if( abs(f_n - y) < eps ):
        return 'IsFibo'
    f_n = Fib(n+1)
    if( abs(f_n - y) < eps ):
        return 'IsFibo'
    return 'IsNotFibo'
    
if __name__ == '__main__':

    result = solve(89)
    print(result)
