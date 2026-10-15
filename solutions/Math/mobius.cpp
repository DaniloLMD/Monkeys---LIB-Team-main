void mobius() {
    mu[1]=1;
    for(int i=2; i<=N; i++){
        mu[i]--;
        for(int j=i+i; j<=N; j+=i) mu[j] -= mu[i];
    }
}