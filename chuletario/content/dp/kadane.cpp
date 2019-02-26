int kadane1D(vi & arr, int& st, int& end, int n){
    int sum = 0, i, maxSum = -INF, ls = 0;
    end = -1; //Es simplemente un valor inicial
    for (i = 0; i < n; ++i){
        sum += arr[i];
        if (sum < 0)
            sum = 0, ls = i+1;
        else if (sum > maxSum)
            maxSum = sum, st = ls, end = i;
    }
    if (end != -1)  return maxSum; //Habia al menos un numero >=0
    maxSum = arr[0]; st=end=0;//else: todos <0, buscamos el maximo
    for (i = 1; i < n; i++)
        if (arr[i] > maxSum)
            maxSum = arr[i], st = end = i;
    return maxSum;
}

int fleft, fright, ftop, fbottom;//valores finales
int kadane2D(vvi m, int r, int c){
    int maxSum = -INF, left, right, i, sum, st, end;
    vi temp(r, 0);
    for (left = 0; left < c; ++left){
		fill (temp.begin(), temp.end(), 0);
        for (right = left; right < c; ++right){
            for (i = 0; i < r; ++i)
                temp[i] += m[i][right];
            sum = kadane1D(temp, st, end, r);
            if (sum > maxSum){
                maxSum = sum; 
                fleft = left; fright = right;
                ftop = st; fbottom = end;
	}}}
	return maxSum;
}
