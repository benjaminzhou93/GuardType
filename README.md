# GuardType
A tool to observe array sort, numerical algorithm(ensure mutithread safe)
    
    
      MAIN_CPP
      Console output automaticly when array sort {3, 5, 1, 11, 7};
                        TRACE: GT[0] > GT[1] = 0
                        TRACE: GT[1] > GT[2] = 1
                        TRACE: GT[1] = GT[2]
                        EXPRES:GT[1] = 1
    3  [1]  1   11   7
                        TRACE: GT[2] = 5
                        EXPRES:GT[2] = 5
    3   1  [5]  11   7
                        TRACE: GT[2] > GT[3] = 0
                        TRACE: GT[3] > GT[4] = 1
                        TRACE: GT[3] = GT[4]
                        EXPRES:GT[3] = 7
    3   1   5  [7]  7
                        TRACE: GT[4] = 11
                        EXPRES:GT[4] = 11
    3   1   5   7  [11]
                        TRACE: GT[0] > GT[1] = 1
                        TRACE: GT[0] = GT[1]
                        EXPRES:GT[0] = 1
    [1]  1   5   7   11
                        TRACE: GT[1] = 3
                        EXPRES:GT[1] = 3
    1  [3]  5   7   11
                        TRACE: GT[1] > GT[2] = 0
                        TRACE: GT[2] > GT[3] = 0
                        TRACE: GT[0] > GT[1] = 0
                        TRACE: GT[1] > GT[2] = 0
                        TRACE: GT[0] > GT[1] = 0
    1  3  5  7  11
    
    
    
    
    
    
    
    MANUAL_CPP
                        TRACE: Pi = 3.14159
                        TRACE: r = 4.1
                        TRACE: r * r = 16.81
                        EXPRES: = 16.81
                        TRACE: Pi * 16.81 = 52.8102
                        EXPRES: = 52.8102
                        EXPRES:s = 3.14159*(4.1*4.1)
                        TRACE: a1[1]++ = 0
                        EXPRES:a1[1] = 1
    0  [1]  0   0   0
                        TRACE: a2[1][2] *= 1 = 0
                        EXPRES:a2[1][2] = 0
    0   0   0
    0   0  [0]
                        TRACE: array[0][2][3] = 1
                        EXPRES:array[0][2][3] = 1
    1   2   3   4
    8   0   0   0
    0   0   0  [1]
    
    16   0   0   0
    20   0   0   0
    24   0   0   0
    
    0   0   0   0   1
                        TRACE: GT = 1
    accumulate result: 1
                        TRACE: GT = 3
    ValueBeReaded: 3
                        TRACE: GT++ = 3
                        EXPRES:GT = 3+1
    Changed to newValue: 4
                        TRACE: GT += 3 = 7
                        EXPRES:GT = 3+1+3
    newValue: 7 oldValue: 4
    
    
    
    
    
    
    
    
    EFFICIENT (Part1 TURN OFF OutOfIndex Detect, Function callback, Multithread safe, Output trace)
    
    GT cost: 0.000105213    sys cost: 4.613e-06    rate: 22.8079    n=1
    GT cost: 0.000111313    sys cost: 2.4813e-05    rate: 4.48608    n++
    GT cost: 0.000113213    sys cost: 2.4713e-05    rate: 4.58111    n--
    GT cost: 9.2813e-05    sys cost: 2.5513e-05    rate: 3.63787    n+=1
    GT cost: 9.8113e-05    sys cost: 2.5713e-05    rate: 3.8157    n-=1
    GT cost: 9.3513e-05    sys cost: 2.4713e-05    rate: 3.78396    n*=1
    GT cost: 0.000135413    sys cost: 0.000115413    rate: 1.17329    n/=1
    GT cost: 0.000140613    sys cost: 0.000113213    rate: 1.24202    n%=1
    GT cost: 9.3913e-05    sys cost: 2.4613e-05    rate: 3.81559    n^=1
    GT cost: 0.000109113    sys cost: 2.4213e-05    rate: 4.50638    n<<=1
    GT cost: 0.000111513    sys cost: 2.9513e-05    rate: 3.77844    n>>=1
    GT cost: 0.000103913    sys cost: 6.313e-06    rate: 16.4602    n+1
    GT cost: 0.000102913    sys cost: 5.713e-06    rate: 18.0138    n-1
    GT cost: 0.000102213    sys cost: 4.213e-06    rate: 24.2613    n*1
    GT cost: 0.000136613    sys cost: 5.513e-06    rate: 24.7802    n/1
    GT cost: 0.000142513    sys cost: 4.913e-06    rate: 29.0073    n%1
    GT cost: 0.000103713    sys cost: 5.713e-06    rate: 18.1539    n^1
    GT cost: 0.000108713    sys cost: 5.113e-06    rate: 21.2621    n&1
    GT cost: 7.0713e-05    sys cost: 5.613e-06    rate: 12.5981    ~n
    GT cost: 7.7313e-05    sys cost: 5.213e-06    rate: 14.8308    !n
    GT cost: 0.000119213    sys cost: 4.813e-06    rate: 24.769    n<<1
    GT cost: 0.000119613    sys cost: 5.313e-06    rate: 22.5133    n>>1
    GT cost: 0.000114413    sys cost: 1.1713e-05    rate: 9.76804    n&&1
    GT cost: 0.000138313    sys cost: 1.0513e-05    rate: 13.1564    n||1
    GT cost: 0.000118213    sys cost: 4.713e-06    rate: 25.0823    n<1
    GT cost: 0.000105413    sys cost: 4.413e-06    rate: 23.8869    n>1
    GT cost: 0.000107913    sys cost: 4.613e-06    rate: 23.3932    n<=1
    GT cost: 0.000120713    sys cost: 6.213e-06    rate: 19.4291    n>=1
    GT cost: 0.000105913    sys cost: 6.613e-06    rate: 16.0159    n==1
    GT cost: 0.000109713    sys cost: 4.313e-06    rate: 25.4377    n!=1
    GT cost: 0.000108513    sys cost: 2.1713e-05    rate: 4.99761    n=n
    GT cost: 0.000117913    sys cost: 3.3513e-05    rate: 3.51843    n+=n
    GT cost: 0.000113213    sys cost: 2.9713e-05    rate: 3.81022    n-=n
    GT cost: 0.000114113    sys cost: 3.5613e-05    rate: 3.20425    n*=n
    GT cost: 0.000290113    sys cost: 5.1713e-05    rate: 5.61006    n=1;n/=n
    GT cost: 0.000288213    sys cost: 4.8913e-05    rate: 5.89236    n=1;n%=n
    GT cost: 0.000124413    sys cost: 4.3113e-05    rate: 2.88574    n^=n
    GT cost: 0.000108213    sys cost: 2.6713e-05    rate: 4.05095    n<<=n
    GT cost: 0.000129713    sys cost: 2.9213e-05    rate: 4.44025    n>>=n
    GT cost: 0.000126113    sys cost: 5.813e-06    rate: 21.695    n+n
    GT cost: 0.000129613    sys cost: 1.1613e-05    rate: 11.161    n-n
    GT cost: 0.000118413    sys cost: 5.913e-06    rate: 20.0259    n*n
    GT cost: 0.000316313    sys cost: 2.2113e-05    rate: 14.3044    n=1;n/n
    GT cost: 0.000338613    sys cost: 1.9713e-05    rate: 17.1771    n=1;n%n
    GT cost: 0.000133513    sys cost: 1.3513e-05    rate: 9.88034    n^n
    GT cost: 0.000115713    sys cost: 9.813e-06    rate: 11.7918    n&n
    GT cost: 0.000132913    sys cost: 1.1213e-05    rate: 11.8535    n<<n
    GT cost: 0.000130813    sys cost: 1.0813e-05    rate: 12.0978    n>>n
    GT cost: 0.000159113    sys cost: 1.3213e-05    rate: 12.0422    n&&n
    GT cost: 0.000106713    sys cost: 8.613e-06    rate: 12.3898    n||n
    GT cost: 0.000131813    sys cost: 1.0313e-05    rate: 12.7812    n<n
    GT cost: 0.000138213    sys cost: 1.1813e-05    rate: 11.7001    n>n
    GT cost: 0.000139713    sys cost: 1.2413e-05    rate: 11.2554    n<=n
    GT cost: 0.000142213    sys cost: 1.1013e-05    rate: 12.9132    n>=n
    GT cost: 0.000139313    sys cost: 1.2713e-05    rate: 10.9583    n==n
    GT cost: 0.000168013    sys cost: 1.5413e-05    rate: 10.9007    n!=n
    GT cost: 0.000138413    sys cost: 5.813e-06    rate: 23.8109    n=arr[0]
    GT cost: 0.000134013    sys cost: 3.1813e-05    rate: 4.21252    n+=arr[0]
    GT cost: 0.000139113    sys cost: 3.3213e-05    rate: 4.18851    n-=arr[0]
    GT cost: 0.000135413    sys cost: 3.6913e-05    rate: 3.66844    n*=arr[0]
    GT cost: 0.000270213    sys cost: 0.000112113    rate: 2.41018    arr[0]=1;n/=arr[0]
    GT cost: 0.000247713    sys cost: 0.000113213    rate: 2.18803    arr[0]=1;n%=arr[0]
    GT cost: 0.000141013    sys cost: 3.6313e-05    rate: 3.88326    n^=arr[0]
    GT cost: 0.000150113    sys cost: 3.1313e-05    rate: 4.79395    n<<=arr[0]
    GT cost: 0.000149713    sys cost: 3.1613e-05    rate: 4.7358    n>>=arr[0]
    GT cost: 0.000102713    sys cost: 1.3313e-05    rate: 7.71524    arr[0]+arr[0]
    GT cost: 0.000138913    sys cost: 1.1613e-05    rate: 11.9619    n-arr[0]
    GT cost: 0.000150913    sys cost: 1.3013e-05    rate: 11.5971    n*arr[0]
    GT cost: 0.000153913    sys cost: 1.0613e-05    rate: 14.5023    arr[0]=1;n/arr[0]
    GT cost: 0.000242713    sys cost: 1.8913e-05    rate: 12.8331    arr[0]=1;n%arr[0]
    GT cost: 0.000103013    sys cost: 6.413e-06    rate: 16.0632    n^arr[0]
    GT cost: 0.000163613    sys cost: 1.6113e-05    rate: 10.1541    n&arr[0]
    GT cost: 4.3313e-05    sys cost: 5.213e-06    rate: 8.30865    ~arr[0]
    GT cost: 4.1613e-05    sys cost: 5.313e-06    rate: 7.8323    !arr[0]
    GT cost: 0.000158613    sys cost: 1.1213e-05    rate: 14.1455    n<<arr[0]
    GT cost: 0.000159513    sys cost: 1.2213e-05    rate: 13.0609    n>>arr[0]
    GT cost: 0.000184913    sys cost: 1.2013e-05    rate: 15.3927    n&&arr[0]
    GT cost: 0.000173913    sys cost: 1.1613e-05    rate: 14.9757    n||arr[0]
    GT cost: 0.000155113    sys cost: 1.2513e-05    rate: 12.3961    n<arr[0]
    GT cost: 0.000149613    sys cost: 1.2113e-05    rate: 12.3514    n>arr[0]
    GT cost: 0.000146913    sys cost: 1.1413e-05    rate: 12.8724    n<=arr[0]
    GT cost: 0.000147913    sys cost: 1.1813e-05    rate: 12.5212    n>=arr[0]
    GT cost: 0.000148113    sys cost: 1.2313e-05    rate: 12.029    n==arr[0]
    GT cost: 0.000147713    sys cost: 1.6913e-05    rate: 8.7337    n!=arr[0]
    GT cost: 0.000109713    sys cost: 2.3613e-05    rate: 4.6463    arr[0]=arr[0]
    GT cost: 5.8413e-05    sys cost: 2.5713e-05    rate: 2.27173    arr[0]++
    GT cost: 5.5813e-05    sys cost: 2.5113e-05    rate: 2.22247    arr[0]--
    GT cost: 0.000109113    sys cost: 3.0513e-05    rate: 3.57595    arr[0]+=arr[0]
    GT cost: 0.000113513    sys cost: 2.9613e-05    rate: 3.83322    arr[0]-=arr[0]
    GT cost: 0.000114513    sys cost: 3.6113e-05    rate: 3.17096    arr[0]*=arr[0]
    GT cost: 0.000221013    sys cost: 5.9413e-05    rate: 3.71994    arr[0]=1;arr[0]/=arr[0]
    GT cost: 0.000216213    sys cost: 5.3913e-05    rate: 4.01041    arr[0]=1;arr[0]%=arr[0]
    GT cost: 8.6113e-05    sys cost: 3.0813e-05    rate: 2.7947    arr[0]^=arr[0]
    GT cost: 0.000131513    sys cost: 2.9813e-05    rate: 4.41126    arr[0]<<=arr[0]
    GT cost: 0.000127913    sys cost: 3.4713e-05    rate: 3.68487    arr[0]>>=arr[0]
    GT cost: 9.5513e-05    sys cost: 1.2513e-05    rate: 7.6331    arr[0]+arr[0]
    GT cost: 9.9913e-05    sys cost: 1.2713e-05    rate: 7.85912    arr[0]-arr[0]
    GT cost: 0.000101113    sys cost: 1.2313e-05    rate: 8.21189    arr[0]*arr[0]
    GT cost: 0.000154313    sys cost: 2.1313e-05    rate: 7.24032    arr[0]=1;arr[0]/arr[0]
    GT cost: 0.000183413    sys cost: 1.8613e-05    rate: 9.85403    arr[0]=1;arr[0]%arr[0]
    GT cost: 9.6313e-05    sys cost: 1.1913e-05    rate: 8.0847    arr[0]^arr[0]
    GT cost: 0.000100513    sys cost: 1.1613e-05    rate: 8.65521    arr[0]&arr[0]
    GT cost: 9.5513e-05    sys cost: 1.1613e-05    rate: 8.22466    arr[0]<<arr[0]
    GT cost: 0.000100113    sys cost: 1.3113e-05    rate: 7.63464    arr[0]>>arr[0]
    GT cost: 0.000111813    sys cost: 9.113e-06    rate: 12.2696    arr[0]&&arr[0]
    GT cost: 5.2113e-05    sys cost: 1.0913e-05    rate: 4.77531    arr[0]||arr[0]
    GT cost: 0.000102313    sys cost: 1.2413e-05    rate: 8.24241    arr[0]<arr[0]
    GT cost: 9.6313e-05    sys cost: 1.1313e-05    rate: 8.51348    arr[0]>arr[0]
    GT cost: 9.7413e-05    sys cost: 1.2013e-05    rate: 8.10897    arr[0]<=arr[0]
    GT cost: 9.5313e-05    sys cost: 1.1713e-05    rate: 8.13737    arr[0]>=arr[0]
    GT cost: 7.0913e-05    sys cost: 6.313e-06    rate: 11.2329    arr[0]==arr[0]
    GT cost: 7.1113e-05    sys cost: 1.1913e-05    rate: 5.96936    arr[0]!=arr[0]
    GT cost: 5.6213e-05    sys cost: 6.213e-06    rate: 9.04764    arr[0]=1
    GT cost: 5.7713e-05    sys cost: 2.6213e-05    rate: 2.20169    arr[0]++
    GT cost: 5.5913e-05    sys cost: 2.5313e-05    rate: 2.20887    arr[0]--
    GT cost: 5.6213e-05    sys cost: 2.9913e-05    rate: 1.87922    arr[0]+=1
    GT cost: 5.5013e-05    sys cost: 2.5413e-05    rate: 2.16476    arr[0]-=1
    GT cost: 4.8513e-05    sys cost: 2.5613e-05    rate: 1.89408    arr[0]*=1
    GT cost: 4.5413e-05    sys cost: 0.000111013    rate: 0.409078    arr[0]/=1
    GT cost: 4.8913e-05    sys cost: 0.000111613    rate: 0.438237    arr[0]%=1
    GT cost: 5.8013e-05    sys cost: 2.5613e-05    rate: 2.26498    arr[0]^=1
    GT cost: 5.6313e-05    sys cost: 2.5513e-05    rate: 2.20723    arr[0]<<=1
    GT cost: 5.6013e-05    sys cost: 2.5513e-05    rate: 2.19547    arr[0]>>=1
    GT cost: 4.2713e-05    sys cost: 5.713e-06    rate: 7.47646    arr[0]+1
    GT cost: 4.3013e-05    sys cost: 6.113e-06    rate: 7.03632    arr[0]-1
    GT cost: 4.2513e-05    sys cost: 6.113e-06    rate: 6.95452    arr[0]*1
    GT cost: 4.1813e-05    sys cost: 5.113e-06    rate: 8.17778    arr[0]/1
    GT cost: 4.0113e-05    sys cost: 1.1013e-05    rate: 3.64233    arr[0]%1
    GT cost: 4.1213e-05    sys cost: 5.613e-06    rate: 7.34242    arr[0]^1
    GT cost: 4.0013e-05    sys cost: 5.713e-06    rate: 7.00385    arr[0]&1
    GT cost: 4.1413e-05    sys cost: 7.413e-06    rate: 5.58654    arr[0]<<1
    GT cost: 4.8613e-05    sys cost: 5.813e-06    rate: 8.36281    arr[0]>>1
    GT cost: 5.1713e-05    sys cost: 1.0913e-05    rate: 4.73866    arr[0]&&1
    GT cost: 5.0713e-05    sys cost: 1.2213e-05    rate: 4.15238    arr[0]||1
    GT cost: 3.9213e-05    sys cost: 6.713e-06    rate: 5.84135    arr[0]<1
    GT cost: 4.0513e-05    sys cost: 6.813e-06    rate: 5.94643    arr[0]>1
    GT cost: 3.9613e-05    sys cost: 5.313e-06    rate: 7.45586    arr[0]<=1
    GT cost: 3.9713e-05    sys cost: 5.413e-06    rate: 7.3366    arr[0]>=1
    GT cost: 4.4013e-05    sys cost: 5.613e-06    rate: 7.84126    arr[0]==1
    GT cost: 3.9213e-05    sys cost: 5.713e-06    rate: 6.86382    arr[0]!=1
    GT cost: 0.000108613    sys cost: 4.813e-06    rate: 22.5666    1+n
    GT cost: 0.000112913    sys cost: 9.813e-06    rate: 11.5065    1-n
    GT cost: 0.000112913    sys cost: 5.513e-06    rate: 20.4812    1*n
    GT cost: 0.000376913    sys cost: 1.2213e-05    rate: 30.8616    n=1;1/n
    GT cost: 0.000267313    sys cost: 7.513e-06    rate: 35.5801    n=1;1%n
    GT cost: 9.2013e-05    sys cost: 2.513e-06    rate: 36.6148    1^n
    GT cost: 8.5813e-05    sys cost: 1.613e-06    rate: 53.2009    1&n
    GT cost: 8.3013e-05    sys cost: 1.713e-06    rate: 48.4606    1<<n
    GT cost: 8.2113e-05    sys cost: 1.713e-06    rate: 47.9352    1>>n
    GT cost: 9.9513e-05    sys cost: 1.713e-06    rate: 58.0928    1&&n
    GT cost: 8.2113e-05    sys cost: 1.1913e-05    rate: 6.89272    int x=1; x||n
    GT cost: 8.5113e-05    sys cost: 2.313e-06    rate: 36.7977    1<n
    GT cost: 0.000116313    sys cost: 5.413e-06    rate: 21.4877    1>n
    GT cost: 0.000120113    sys cost: 4.613e-06    rate: 26.0379    1<=n
    GT cost: 0.000115513    sys cost: 2.713e-06    rate: 42.5776    1>=n
    GT cost: 0.000132813    sys cost: 2.513e-06    rate: 52.8504    1==n
    GT cost: 0.000115913    sys cost: 1.813e-06    rate: 63.9344    1!=n
    GT cost: 4.8613e-05    sys cost: 3.413e-06    rate: 14.2435    1+arr[0]
    GT cost: 3.9513e-05    sys cost: 2.113e-06    rate: 18.7    1-arr[0]
    GT cost: 3.7813e-05    sys cost: 2.113e-06    rate: 17.8954    1*arr[0]
    GT cost: 7.1313e-05    sys cost: 6.113e-06    rate: 11.6658    arr[0]=1;1/arr[0]
    GT cost: 6.9813e-05    sys cost: 6.313e-06    rate: 11.0586    arr[0]=1;1%arr[0]
    GT cost: 3.6713e-05    sys cost: 2.113e-06    rate: 17.3748    1^arr[0]
    GT cost: 3.6513e-05    sys cost: 4.513e-06    rate: 8.09063    1&arr[0]
    GT cost: 3.6613e-05    sys cost: 2.113e-06    rate: 17.3275    1<<arr[0]
    GT cost: 3.6413e-05    sys cost: 2.113e-06    rate: 17.2328    1>>arr[0]
    GT cost: 3.5113e-05    sys cost: 2.013e-06    rate: 17.4431    1&&arr[0]
    GT cost: 1.6013e-05    sys cost: 1.4213e-05    rate: 1.12664    int x=1; x||arr[0]
    GT cost: 3.7413e-05    sys cost: 2.113e-06    rate: 17.7061    1<arr[0]
    GT cost: 2.7713e-05    sys cost: 1.913e-06    rate: 14.4867    1>arr[0]
    GT cost: 3.9413e-05    sys cost: 2.013e-06    rate: 19.5792    1<=arr[0]
    GT cost: 4.0613e-05    sys cost: 2.113e-06    rate: 19.2205    1>=arr[0]
    GT cost: 3.8213e-05    sys cost: 6.113e-06    rate: 6.2511    1==arr[0]
    GT cost: 3.9813e-05    sys cost: 2.313e-06    rate: 17.2127    1!=arr[0]
    GT cost: 9.3013e-05    sys cost: 5.913e-06    rate: 15.7303    l+n
    GT cost: 9.0113e-05    sys cost: 5.813e-06    rate: 15.502    l-n
    GT cost: 8.7913e-05    sys cost: 5.813e-06    rate: 15.1235    l*n
    GT cost: 0.000282213    sys cost: 1.0213e-05    rate: 27.6327    n=1;l/n
    GT cost: 0.000287913    sys cost: 1.0013e-05    rate: 28.7539    n=1;l%n
    GT cost: 9.3213e-05    sys cost: 8.913e-06    rate: 10.4581    l^n
    GT cost: 8.8713e-05    sys cost: 5.813e-06    rate: 15.2611    l&n
    GT cost: 8.8513e-05    sys cost: 5.813e-06    rate: 15.2267    l<<n
    GT cost: 9.0913e-05    sys cost: 5.913e-06    rate: 15.3751    l>>n
    GT cost: 0.000135813    sys cost: 1.3713e-05    rate: 9.90396    l&&n
    GT cost: 0.000127913    sys cost: 1.1513e-05    rate: 11.1103    l||n
    GT cost: 0.000138313    sys cost: 1.2213e-05    rate: 11.3251    l<n
    GT cost: 0.000155813    sys cost: 1.5613e-05    rate: 9.9797    l>n
    GT cost: 0.000165913    sys cost: 1.4413e-05    rate: 11.5113    l<=n
    GT cost: 0.000163113    sys cost: 1.4413e-05    rate: 11.3171    l>=n
    GT cost: 0.000189313    sys cost: 2.1613e-05    rate: 8.75922    l==n
    GT cost: 0.000137013    sys cost: 1.6813e-05    rate: 8.14923    l!=n
    GT cost: 0.000174513    sys cost: 1.3313e-05    rate: 13.1085    f=arr[0]
    GT cost: 0.000176913    sys cost: 4.4713e-05    rate: 3.95663    f+=arr[0]
    GT cost: 0.000166213    sys cost: 4.0513e-05    rate: 4.10271    f-=arr[0]
    GT cost: 8.4613e-05    sys cost: 8.1413e-05    rate: 1.03931    f*=arr[0]
    GT cost: 0.000205313    sys cost: 6.8113e-05    rate: 3.0143    arr[0]=1;f/=arr[0]
    GT cost: 0.000155113    sys cost: 1.2313e-05    rate: 12.5975    f-arr[0]
    GT cost: 0.000166413    sys cost: 1.2413e-05    rate: 13.4063    f*arr[0]
    GT cost: 0.000193013    sys cost: 1.8713e-05    rate: 10.3144    arr[0]=1;f/arr[0]
    GT cost: 4.2913e-05    sys cost: 6.013e-06    rate: 7.1367    ~arr[0]
    GT cost: 4.3813e-05    sys cost: 5.613e-06    rate: 7.80563    !arr[0]
    GT cost: 0.000171213    sys cost: 1.6613e-05    rate: 10.306    f&&arr[0]
    GT cost: 0.000157713    sys cost: 1.1413e-05    rate: 13.8187    f||arr[0]
    GT cost: 0.000168213    sys cost: 1.3513e-05    rate: 12.4482    f<arr[0]
    GT cost: 0.000164313    sys cost: 1.7913e-05    rate: 9.17284    f>arr[0]
    GT cost: 0.000160913    sys cost: 1.4713e-05    rate: 10.9368    f<=arr[0]
    GT cost: 0.000159413    sys cost: 1.3013e-05    rate: 12.2503    f>=arr[0]
    GT cost: 0.000167413    sys cost: 1.3113e-05    rate: 12.7669    f==arr[0]
    GT cost: 0.000132413    sys cost: 6.113e-06    rate: 21.6609    f!=arr[0]
    GT cost: 6.4513e-05    sys cost: 1.3813e-05    rate: 4.67046    farr[0]=arr[0]
    GT cost: 0.000117213    sys cost: 3.8713e-05    rate: 3.02774    farr[0]+=arr[0]
    GT cost: 0.000122213    sys cost: 3.7513e-05    rate: 3.25788    farr[0]-=arr[0]
    GT cost: 0.000121413    sys cost: 4.4213e-05    rate: 2.74609    farr[0]*=arr[0]
    GT cost: 0.000182013    sys cost: 7.0713e-05    rate: 2.57397    arr[0]=1;farr[0]/=arr[0]
    GT cost: 9.7613e-05    sys cost: 1.2713e-05    rate: 7.6782    farr[0]-arr[0]
    GT cost: 9.8613e-05    sys cost: 1.4513e-05    rate: 6.7948    farr[0]*arr[0]
    GT cost: 0.000156613    sys cost: 1.9413e-05    rate: 8.06743    arr[0]=1;farr[0]/arr[0]
    GT cost: 4.1313e-05    sys cost: 5.613e-06    rate: 7.36024    !farr[0]
    GT cost: 0.000116613    sys cost: 1.5613e-05    rate: 7.46897    farr[0]&&arr[0]
    GT cost: 5.5313e-05    sys cost: 1.8713e-05    rate: 2.95586    farr[0]||arr[0]
    GT cost: 0.000102013    sys cost: 1.4313e-05    rate: 7.1273    farr[0]<arr[0]
    GT cost: 9.9713e-05    sys cost: 1.4313e-05    rate: 6.9666    farr[0]>arr[0]
    GT cost: 0.000104113    sys cost: 1.2313e-05    rate: 8.45553    farr[0]<=arr[0]
    GT cost: 9.2813e-05    sys cost: 1.3613e-05    rate: 6.81797    farr[0]>=arr[0]
    GT cost: 9.4213e-05    sys cost: 1.2013e-05    rate: 7.84259    farr[0]==arr[0]
    GT cost: 9.3513e-05    sys cost: 1.2413e-05    rate: 7.53347    farr[0]!=arr[0]
    GT cost: 0.000131613    sys cost: 6.913e-06    rate: 19.0385    int x = arr[0]+arr[1]
    GT cost: 0.000203413    sys cost: 1.1513e-05    rate: 17.6681    int x = arr[0]+arr[1]+arr[2]
    GT cost: 0.000265313    sys cost: 1.2913e-05    rate: 20.5462    int x = arr[0]+arr[1]+arr[2]+arr[3]
    GT cost: 0.000381313    sys cost: 2.0413e-05    rate: 18.6799    int x = arr[0]+arr[1]+arr[2]+arr[3]+arr[4]
    GT cost: 0.000241313    sys cost: 5.613e-06    rate: 42.9918    int x = arr2[0][0]+arr2[1][1]
    GT cost: 0.000407813    sys cost: 1.1513e-05    rate: 35.422    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]
    GT cost: 0.000424313    sys cost: 1.2313e-05    rate: 34.4606    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]
    GT cost: 0.000515513    sys cost: 1.1413e-05    rate: 45.1689    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]+arr2[4][4]
    GT cost: 0.000281013    sys cost: 2.913e-06    rate: 96.4686    int x = arr3[0][0][0]+arr3[1][1][1]
    GT cost: 0.000436513    sys cost: 1.0813e-05    rate: 40.3693    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]
    GT cost: 0.000845913    sys cost: 9.313e-06    rate: 90.8314    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]
    GT cost: 0.000708413    sys cost: 8.613e-06    rate: 82.2493    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]+arr3[4][4][4]
    
    
    
    
    
    
    
    
    EFFICIENT (Part2 TURN ON OutOfIndex Detect, Function callback, Multithread safe, Output trace)
    
    runTimeOfFor: 3.116e-05
    2.2384e-05     func0()
    2.7184e-05     func1(1)
    2.9884e-05     func2(1, 2)
    4.5284e-05     volatile Cinner c
    5.384e-06     volatile int n; n=1;
    0.00199908     Bool a
    0.00262118     Char a
    0.00148788     Short a
    0.00150368     Int a
    0.00213518     Long a
    0.00167488     LLong a
    0.00154968     Float a
    0.00170278     Double a
    0.000278884     string s
    0.00269138     String s
    1.0684e-05     int a(0); a=0;
    0.00289838     Bool a(0)
    0.00257518     Char a(0)
    0.00207368     Short a(0)
    0.00269158     Int a(0)
    0.00241698     Long a(0)
    0.00181098     LLong a(0)
    0.00241308     Float a(0)
    0.00246328     Double a(0)
    0.000416384     string s("s")
    0.00239558     String s("s")
    5.384e-06     volatile int a[10]; a[0]=0
    0.00129898     int * p = new int; delete p
    0.00147218     int * p = new int[10]; delete[] p
    0.0118072     IntArr arr(10)
    0.0130552     IntArr2D arr(3, 3)
    0.0114022     IntArr3D arr(2, 2, 2)
    0.00622798     IntArray(2, 2, 2) arr
    5.184e-06     volatile int a[2][2][2]; a[0][0][0]=0;
    0.000346784     std::mutex m;
    0.00388528     std::mutex m[10];
    0.000711284     std::recursive_mutex m;
    0.00601248     std::recursive_mutex m[10];
    0.000151284     std::atomic<unsigned int> a; a=0
    0.000344084     std::lock_guard<std::mutex> l(m);
    0.000438484     std::unique_lock<std::mutex> l(m);
    0.000828684     std::lock_guard<std::recursive_mutex> l(rm);
    0.000851884     std::unique_lock<std::recursive_mutex> l(rm);
    GT cost: 0.00194118    sys cost: 1.584e-06    rate: 1225.49    n=1
    GT cost: 0.00426008    sys cost: 2.2684e-05    rate: 187.801    n++
    GT cost: 0.00393498    sys cost: 2.4384e-05    rate: 161.376    n--
    GT cost: 0.00204608    sys cost: 2.3984e-05    rate: 85.3104    n+=1
    GT cost: 0.00171348    sys cost: 2.4884e-05    rate: 68.8589    n-=1
    GT cost: 0.00194118    sys cost: 2.5284e-05    rate: 76.7752    n*=1
    GT cost: 0.00206788    sys cost: 0.000111884    rate: 18.4824    n/=1
    GT cost: 0.00188158    sys cost: 0.000111384    rate: 16.8928    n%=1
    GT cost: 0.00189718    sys cost: 2.2984e-05    rate: 82.5437    n^=1
    GT cost: 0.00215938    sys cost: 2.5484e-05    rate: 84.7349    n<<=1
    GT cost: 0.00162218    sys cost: 2.4384e-05    rate: 66.5266    n>>=1
    GT cost: 0.00329398    sys cost: 5.484e-06    rate: 600.654    n+1
    GT cost: 0.00310838    sys cost: 1.584e-06    rate: 1962.36    n-1
    GT cost: 0.00305878    sys cost: 1.584e-06    rate: 1931.05    n*1
    GT cost: 0.00380528    sys cost: 1.584e-06    rate: 2402.33    n/1
    GT cost: 0.00298978    sys cost: 5.284e-06    rate: 565.818    n%1
    GT cost: 0.00389488    sys cost: 5.384e-06    rate: 723.418    n^1
    GT cost: 0.00370478    sys cost: 5.784e-06    rate: 640.523    n&1
    GT cost: 0.00463898    sys cost: 4.284e-06    rate: 1082.86    ~n
    GT cost: 0.00488648    sys cost: 1.484e-06    rate: 3292.78    !n
    GT cost: 0.00346168    sys cost: 2.484e-06    rate: 1393.59    n<<1
    GT cost: 0.00346308    sys cost: 4.484e-06    rate: 772.32    n>>1
    GT cost: 0.00241038    sys cost: 1.0784e-05    rate: 223.515    n&&1
    GT cost: 0.00235868    sys cost: 4.784e-06    rate: 493.036    n||1
    GT cost: 0.00262868    sys cost: 1.0284e-05    rate: 255.609    n<1
    GT cost: 0.00269468    sys cost: 1.584e-06    rate: 1701.19    n>1
    GT cost: 0.00199508    sys cost: 5.384e-06    rate: 370.558    n<=1
    GT cost: 0.00183468    sys cost: 1.0884e-05    rate: 168.567    n>=1
    GT cost: 0.00248678    sys cost: 5.584e-06    rate: 445.341    n==1
    GT cost: 0.00239118    sys cost: 1.584e-06    rate: 1509.59    n!=1
    GT cost: 0.00224728    sys cost: 1.9084e-05    rate: 117.757    n=n
    GT cost: 0.00294258    sys cost: 3.2884e-05    rate: 89.4838    n+=n
    GT cost: 0.00221118    sys cost: 2.8884e-05    rate: 76.5539    n-=n
    GT cost: 0.00287328    sys cost: 4.3084e-05    rate: 66.6903    n*=n
    GT cost: 0.00435838    sys cost: 3.9384e-05    rate: 110.664    n=1;n/=n
    GT cost: 0.00435048    sys cost: 5.3984e-05    rate: 80.5884    n=1;n%=n
    GT cost: 0.00238068    sys cost: 3.4184e-05    rate: 69.6432    n^=n
    GT cost: 0.00240078    sys cost: 2.8984e-05    rate: 82.8314    n<<=n
    GT cost: 0.00304648    sys cost: 2.9084e-05    rate: 104.748    n>>=n
    GT cost: 0.00355318    sys cost: 5.784e-06    rate: 614.313    n+n
    GT cost: 0.00340508    sys cost: 5.684e-06    rate: 599.065    n-n
    GT cost: 0.00330828    sys cost: 1.2784e-05    rate: 258.783    n*n
    GT cost: 0.00601728    sys cost: 9.984e-06    rate: 602.693    n=1;n/n
    GT cost: 0.00580038    sys cost: 1.6884e-05    rate: 343.543    n=1;n%n
    GT cost: 0.00357668    sys cost: 1.0384e-05    rate: 344.442    n^n
    GT cost: 0.00429828    sys cost: 5.684e-06    rate: 756.208    n&n
    GT cost: 0.00411658    sys cost: 1.2984e-05    rate: 317.051    n<<n
    GT cost: 0.00387688    sys cost: 5.784e-06    rate: 670.277    n>>n
    GT cost: 0.00214588    sys cost: 1.2884e-05    rate: 166.554    n&&n
    GT cost: 0.00228218    sys cost: 2.484e-06    rate: 918.754    n||n
    GT cost: 0.00307458    sys cost: 7.484e-06    rate: 410.821    n<n
    GT cost: 0.00275758    sys cost: 5.784e-06    rate: 476.761    n>n
    GT cost: 0.00273368    sys cost: 1.1284e-05    rate: 242.262    n<=n
    GT cost: 0.00268048    sys cost: 5.684e-06    rate: 471.584    n>=n
    GT cost: 0.00261218    sys cost: 5.684e-06    rate: 459.568    n==n
    GT cost: 0.00345248    sys cost: 1.2384e-05    rate: 278.786    n!=n
    GT cost: 0.00273598    sys cost: 4.884e-06    rate: 560.193    n=arr[0]
    GT cost: 0.00269538    sys cost: 3.1884e-05    rate: 84.5372    n+=arr[0]
    GT cost: 0.00305548    sys cost: 2.6284e-05    rate: 116.249    n-=arr[0]
    GT cost: 0.00339858    sys cost: 3.6484e-05    rate: 93.1527    n*=arr[0]
    GT cost: 0.00467088    sys cost: 0.000111184    rate: 42.0104    arr[0]=1;n/=arr[0]
    GT cost: 0.00594268    sys cost: 0.000117084    rate: 50.7557    arr[0]=1;n%=arr[0]
    GT cost: 0.00305968    sys cost: 2.8384e-05    rate: 107.796    n^=arr[0]
    GT cost: 0.00380538    sys cost: 3.6184e-05    rate: 105.168    n<<=arr[0]
    GT cost: 0.00356058    sys cost: 3.1284e-05    rate: 113.815    n>>=arr[0]
    GT cost: 0.00471798    sys cost: 6.384e-06    rate: 739.033    arr[0]+arr[0]
    GT cost: 0.00452388    sys cost: 1.2984e-05    rate: 348.42    n-arr[0]
    GT cost: 0.00537608    sys cost: 1.4184e-05    rate: 379.025    n*arr[0]
    GT cost: 0.00672718    sys cost: 1.0584e-05    rate: 635.599    arr[0]=1;n/arr[0]
    GT cost: 0.00650628    sys cost: 2.0284e-05    rate: 320.759    arr[0]=1;n%arr[0]
    GT cost: 0.00495258    sys cost: 1.3084e-05    rate: 378.522    n^arr[0]
    GT cost: 0.00425868    sys cost: 6.284e-06    rate: 677.703    n&arr[0]
    GT cost: 0.00484538    sys cost: 1.0284e-05    rate: 471.158    ~arr[0]
    GT cost: 0.00491988    sys cost: 5.384e-06    rate: 913.797    !arr[0]
    GT cost: 0.00514598    sys cost: 1.3384e-05    rate: 384.488    n<<arr[0]
    GT cost: 0.00460958    sys cost: 1.2884e-05    rate: 357.776    n>>arr[0]
    GT cost: 0.00388358    sys cost: 1.5784e-05    rate: 246.046    n&&arr[0]
    GT cost: 0.00364528    sys cost: 1.4984e-05    rate: 243.278    n||arr[0]
    GT cost: 0.00406358    sys cost: 1.3584e-05    rate: 299.145    n<arr[0]
    GT cost: 0.00319928    sys cost: 1.0984e-05    rate: 291.268    n>arr[0]
    GT cost: 0.00399458    sys cost: 6.384e-06    rate: 625.718    n<=arr[0]
    GT cost: 0.00303198    sys cost: 1.2484e-05    rate: 242.87    n>=arr[0]
    GT cost: 0.00311588    sys cost: 1.1584e-05    rate: 268.982    n==arr[0]
    GT cost: 0.00327788    sys cost: 6.384e-06    rate: 513.453    n!=arr[0]
    GT cost: 0.00386888    sys cost: 2.0484e-05    rate: 188.873    arr[0]=arr[0]
    GT cost: 0.00479038    sys cost: 2.5584e-05    rate: 187.241    arr[0]++
    GT cost: 0.00451908    sys cost: 2.3884e-05    rate: 189.21    arr[0]--
    GT cost: 0.00279418    sys cost: 3.0784e-05    rate: 90.7674    arr[0]+=arr[0]
    GT cost: 0.00207428    sys cost: 3.0584e-05    rate: 67.8225    arr[0]-=arr[0]
    GT cost: 0.00270688    sys cost: 3.6484e-05    rate: 74.1937    arr[0]*=arr[0]
    GT cost: 0.00338468    sys cost: 4.0084e-05    rate: 84.4398    arr[0]=1;arr[0]/=arr[0]
    GT cost: 0.00380668    sys cost: 4.0484e-05    rate: 94.0293    arr[0]=1;arr[0]%=arr[0]
    GT cost: 0.00212128    sys cost: 3.0884e-05    rate: 68.6855    arr[0]^=arr[0]
    GT cost: 0.00221798    sys cost: 2.9184e-05    rate: 76    arr[0]<<=arr[0]
    GT cost: 0.00242328    sys cost: 3.0884e-05    rate: 78.4641    arr[0]>>=arr[0]
    GT cost: 0.00351748    sys cost: 8.884e-06    rate: 395.935    arr[0]+arr[0]
    GT cost: 0.00342088    sys cost: 5.384e-06    rate: 635.38    arr[0]-arr[0]
    GT cost: 0.00310948    sys cost: 9.384e-06    rate: 331.36    arr[0]*arr[0]
    GT cost: 0.00498168    sys cost: 1.0284e-05    rate: 484.411    arr[0]=1;arr[0]/arr[0]
    GT cost: 0.00444998    sys cost: 1.0584e-05    rate: 420.444    arr[0]=1;arr[0]%arr[0]
    GT cost: 0.00435418    sys cost: 1.2084e-05    rate: 360.326    arr[0]^arr[0]
    GT cost: 0.00378338    sys cost: 6.384e-06    rate: 592.635    arr[0]&arr[0]
    GT cost: 0.00380748    sys cost: 6.284e-06    rate: 605.901    arr[0]<<arr[0]
    GT cost: 0.00327058    sys cost: 6.384e-06    rate: 512.31    arr[0]>>arr[0]
    GT cost: 0.00304678    sys cost: 8.484e-06    rate: 359.121    arr[0]&&arr[0]
    GT cost: 0.00230078    sys cost: 1.0284e-05    rate: 223.725    arr[0]||arr[0]
    GT cost: 0.00218488    sys cost: 5.584e-06    rate: 391.276    arr[0]<arr[0]
    GT cost: 0.00240898    sys cost: 5.184e-06    rate: 464.696    arr[0]>arr[0]
    GT cost: 0.00214898    sys cost: 5.384e-06    rate: 399.143    arr[0]<=arr[0]
    GT cost: 0.00245218    sys cost: 8.884e-06    rate: 276.023    arr[0]>=arr[0]
    GT cost: 0.00258258    sys cost: 5.684e-06    rate: 454.36    arr[0]==arr[0]
    GT cost: 0.00233758    sys cost: 5.284e-06    rate: 442.389    arr[0]!=arr[0]
    GT cost: 0.00126098    sys cost: 1.484e-06    rate: 849.72    arr[0]=1
    GT cost: 0.00301798    sys cost: 2.0284e-05    rate: 148.786    arr[0]++
    GT cost: 0.00350438    sys cost: 3.6384e-05    rate: 96.3166    arr[0]--
    GT cost: 0.00141518    sys cost: 2.0284e-05    rate: 69.7685    arr[0]+=1
    GT cost: 0.00147898    sys cost: 2.3384e-05    rate: 63.2477    arr[0]-=1
    GT cost: 0.00124158    sys cost: 2.6284e-05    rate: 47.2373    arr[0]*=1
    GT cost: 0.00212558    sys cost: 0.000133684    rate: 15.9001    arr[0]/=1
    GT cost: 0.00136238    sys cost: 9.8684e-05    rate: 13.8055    arr[0]%=1
    GT cost: 0.00145718    sys cost: 2.0584e-05    rate: 70.7921    arr[0]^=1
    GT cost: 0.00123758    sys cost: 1.9684e-05    rate: 62.8726    arr[0]<<=1
    GT cost: 0.00151618    sys cost: 1.9684e-05    rate: 77.0262    arr[0]>>=1
    GT cost: 0.00256078    sys cost: 1.584e-06    rate: 1616.66    arr[0]+1
    GT cost: 0.00240488    sys cost: 4.184e-06    rate: 574.781    arr[0]-1
    GT cost: 0.00264278    sys cost: 1.484e-06    rate: 1780.85    arr[0]*1
    GT cost: 0.00250028    sys cost: 2.884e-06    rate: 866.95    arr[0]/1
    GT cost: 0.00232958    sys cost: 3.184e-06    rate: 731.653    arr[0]%1
    GT cost: 0.00254998    sys cost: 1.984e-06    rate: 1285.27    arr[0]^1
    GT cost: 0.00272438    sys cost: 6.284e-06    rate: 433.543    arr[0]&1
    GT cost: 0.00227638    sys cost: 1.384e-06    rate: 1644.79    arr[0]<<1
    GT cost: 0.00241338    sys cost: 1.484e-06    rate: 1626.27    arr[0]>>1
    GT cost: 0.00204458    sys cost: 6.584e-06    rate: 310.538    arr[0]&&1
    GT cost: 0.00175638    sys cost: 7.784e-06    rate: 225.64    arr[0]||1
    GT cost: 0.00160088    sys cost: 1.284e-06    rate: 1246.79    arr[0]<1
    GT cost: 0.00149918    sys cost: 1.684e-06    rate: 890.252    arr[0]>1
    GT cost: 0.00167708    sys cost: 1.484e-06    rate: 1130.11    arr[0]<=1
    GT cost: 0.00171048    sys cost: 2.084e-06    rate: 820.77    arr[0]>=1
    GT cost: 0.00153518    sys cost: 1.484e-06    rate: 1034.49    arr[0]==1
    GT cost: 0.00206138    sys cost: 6.884e-06    rate: 299.446    arr[0]!=1
    GT cost: 0.00229388    sys cost: 2.584e-06    rate: 887.726    1+n
    GT cost: 0.00260008    sys cost: 9.84e-07    rate: 2642.36    1-n
    GT cost: 0.00198088    sys cost: 9.84e-07    rate: 2013.09    1*n
    GT cost: 0.00342258    sys cost: 6.584e-06    rate: 519.834    n=1;1/n
    GT cost: 0.00346058    sys cost: 4.684e-06    rate: 738.81    n=1;1%n
    GT cost: 0.00205758    sys cost: 1.684e-06    rate: 1221.84    1^n
    GT cost: 0.00214448    sys cost: 9.84e-07    rate: 2179.35    1&n
    GT cost: 0.00231678    sys cost: 4.884e-06    rate: 474.362    1<<n
    GT cost: 0.00245028    sys cost: 2.784e-06    rate: 880.131    1>>n
    GT cost: 0.00138378    sys cost: 9.84e-07    rate: 1406.28    1&&n
    GT cost: 0.00149128    sys cost: 8.984e-06    rate: 165.993    int x=1; x||n
    GT cost: 0.00130298    sys cost: 8.84e-07    rate: 1473.96    1<n
    GT cost: 0.00134878    sys cost: 1.684e-06    rate: 800.941    1>n
    GT cost: 0.00150328    sys cost: 3.584e-06    rate: 419.443    1<=n
    GT cost: 0.00128198    sys cost: 9.84e-07    rate: 1302.83    1>=n
    GT cost: 0.00178768    sys cost: 2.384e-06    rate: 749.867    1==n
    GT cost: 0.00137158    sys cost: 9.184e-06    rate: 149.345    1!=n
    GT cost: 0.00289708    sys cost: 3.184e-06    rate: 909.888    1+arr[0]
    GT cost: 0.00237598    sys cost: 2.184e-06    rate: 1087.9    1-arr[0]
    GT cost: 0.00264058    sys cost: 1.684e-06    rate: 1568.04    1*arr[0]
    GT cost: 0.00469478    sys cost: 5.284e-06    rate: 888.491    arr[0]=1;1/arr[0]
    GT cost: 0.00339108    sys cost: 5.384e-06    rate: 629.845    arr[0]=1;1%arr[0]
    GT cost: 0.00293738    sys cost: 5.184e-06    rate: 566.625    1^arr[0]
    GT cost: 0.00243428    sys cost: 1.784e-06    rate: 1364.51    1&arr[0]
    GT cost: 0.00222808    sys cost: 1.684e-06    rate: 1323.09    1<<arr[0]
    GT cost: 0.00260648    sys cost: 3.984e-06    rate: 654.238    1>>arr[0]
    GT cost: 0.00156588    sys cost: 1.684e-06    rate: 929.86    1&&arr[0]
    GT cost: 0.00169358    sys cost: 8.384e-06    rate: 202.002    int x=1; x||arr[0]
    GT cost: 0.00145538    sys cost: 1.384e-06    rate: 1051.58    1<arr[0]
    GT cost: 0.00193568    sys cost: 6.084e-06    rate: 318.16    1>arr[0]
    GT cost: 0.00170208    sys cost: 2.984e-06    rate: 570.403    1<=arr[0]
    GT cost: 0.00149268    sys cost: 1.484e-06    rate: 1005.85    1>=arr[0]
    GT cost: 0.00148008    sys cost: 1.484e-06    rate: 997.361    1==arr[0]
    GT cost: 0.00176128    sys cost: 1.484e-06    rate: 1186.85    1!=arr[0]
    GT cost: 0.00259818    sys cost: 4.684e-06    rate: 554.693    l+n
    GT cost: 0.00257538    sys cost: 5.684e-06    rate: 453.094    l-n
    GT cost: 0.00319098    sys cost: 1.1984e-05    rate: 266.27    l*n
    GT cost: 0.00506658    sys cost: 1.9184e-05    rate: 264.105    n=1;l/n
    GT cost: 0.00372628    sys cost: 8.484e-06    rate: 439.213    n=1;l%n
    GT cost: 0.00286278    sys cost: 8.984e-06    rate: 318.654    l^n
    GT cost: 0.00324318    sys cost: 6.684e-06    rate: 485.216    l&n
    GT cost: 0.00297958    sys cost: 1.1884e-05    rate: 250.722    l<<n
    GT cost: 0.00301778    sys cost: 4.784e-06    rate: 630.808    l>>n
    GT cost: 0.00200348    sys cost: 3.384e-06    rate: 592.046    l&&n
    GT cost: 0.00211888    sys cost: 3.584e-06    rate: 591.206    l||n
    GT cost: 0.00210668    sys cost: 6.784e-06    rate: 310.537    l<n
    GT cost: 0.00241508    sys cost: 7.284e-06    rate: 331.56    l>n
    GT cost: 0.00273868    sys cost: 1.1884e-05    rate: 230.451    l<=n
    GT cost: 0.00253138    sys cost: 1.2084e-05    rate: 209.482    l>=n
    GT cost: 0.00246298    sys cost: 1.8184e-05    rate: 135.448    l==n
    GT cost: 0.00258648    sys cost: 6.784e-06    rate: 381.262    l!=n
    GT cost: 0.00217518    sys cost: 9.484e-06    rate: 229.353    f=arr[0]
    GT cost: 0.00238728    sys cost: 3.5184e-05    rate: 67.8514    f+=arr[0]
    GT cost: 0.00203148    sys cost: 3.4784e-05    rate: 58.4028    f-=arr[0]
    GT cost: 0.00217108    sys cost: 4.3584e-05    rate: 49.8138    f*=arr[0]
    GT cost: 0.00378798    sys cost: 6.4584e-05    rate: 58.6521    arr[0]=1;f/=arr[0]
    GT cost: 0.00345658    sys cost: 6.184e-06    rate: 558.956    f-arr[0]
    GT cost: 0.00355118    sys cost: 6.384e-06    rate: 556.263    f*arr[0]
    GT cost: 0.00454508    sys cost: 1.0384e-05    rate: 437.701    arr[0]=1;f/arr[0]
    GT cost: 0.00382738    sys cost: 2.284e-06    rate: 1675.74    ~arr[0]
    GT cost: 0.00320458    sys cost: 2.284e-06    rate: 1403.06    !arr[0]
    GT cost: 0.00251578    sys cost: 9.984e-06    rate: 251.982    f&&arr[0]
    GT cost: 0.00268268    sys cost: 4.484e-06    rate: 598.279    f||arr[0]
    GT cost: 0.00237748    sys cost: 6.484e-06    rate: 366.669    f<arr[0]
    GT cost: 0.00254638    sys cost: 1.3884e-05    rate: 183.404    f>arr[0]
    GT cost: 0.00286748    sys cost: 5.584e-06    rate: 513.518    f<=arr[0]
    GT cost: 0.00204088    sys cost: 5.184e-06    rate: 393.689    f>=arr[0]
    GT cost: 0.00230378    sys cost: 5.384e-06    rate: 427.895    f==arr[0]
    GT cost: 0.00236178    sys cost: 7.584e-06    rate: 311.417    f!=arr[0]
    GT cost: 0.00207168    sys cost: 8.784e-06    rate: 235.847    farr[0]=arr[0]
    GT cost: 0.00223748    sys cost: 3.6184e-05    rate: 61.8363    farr[0]+=arr[0]
    GT cost: 0.00201438    sys cost: 3.0984e-05    rate: 65.0137    farr[0]-=arr[0]
    GT cost: 0.00237888    sys cost: 3.8284e-05    rate: 62.1378    farr[0]*=arr[0]
    GT cost: 0.00378368    sys cost: 5.6784e-05    rate: 66.6329    arr[0]=1;farr[0]/=arr[0]
    GT cost: 0.00359858    sys cost: 8.084e-06    rate: 445.149    farr[0]-arr[0]
    GT cost: 0.00360648    sys cost: 5.084e-06    rate: 709.379    farr[0]*arr[0]
    GT cost: 0.00472798    sys cost: 9.184e-06    rate: 514.807    arr[0]=1;farr[0]/arr[0]
    GT cost: 0.00336198    sys cost: 1.584e-06    rate: 2122.46    !farr[0]
    GT cost: 0.00287648    sys cost: 7.984e-06    rate: 360.281    farr[0]&&arr[0]
    GT cost: 0.00226738    sys cost: 8.484e-06    rate: 267.254    farr[0]||arr[0]
    GT cost: 0.00266748    sys cost: 7.684e-06    rate: 347.148    farr[0]<arr[0]
    GT cost: 0.00256128    sys cost: 1.0484e-05    rate: 244.304    farr[0]>arr[0]
    GT cost: 0.00255858    sys cost: 1.1384e-05    rate: 224.753    farr[0]<=arr[0]
    GT cost: 0.00241278    sys cost: 5.084e-06    rate: 474.584    farr[0]>=arr[0]
    GT cost: 0.00271908    sys cost: 7.984e-06    rate: 340.567    farr[0]==arr[0]
    GT cost: 0.00232058    sys cost: 7.084e-06    rate: 327.581    farr[0]!=arr[0]
    GT cost: 0.00336538    sys cost: 2.384e-06    rate: 1411.65    int x = arr[0]+arr[1]
    GT cost: 0.00710038    sys cost: 3.384e-06    rate: 2098.22    int x = arr[0]+arr[1]+arr[2]
    GT cost: 0.00892328    sys cost: 5.884e-06    rate: 1516.53    int x = arr[0]+arr[1]+arr[2]+arr[3]
    GT cost: 0.0117892    sys cost: 7.084e-06    rate: 1664.2    int x = arr[0]+arr[1]+arr[2]+arr[3]+arr[4]
    GT cost: 0.00446708    sys cost: 1.684e-06    rate: 2652.66    int x = arr2[0][0]+arr2[1][1]
    GT cost: 0.00826098    sys cost: 3.984e-06    rate: 2073.54    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]
    GT cost: 0.0115425    sys cost: 6.284e-06    rate: 1836.81    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]
    GT cost: 0.0148784    sys cost: 7.284e-06    rate: 2042.61    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]+arr2[4][4]
    GT cost: 0.00565748    sys cost: 6.284e-06    rate: 900.3    int x = arr3[0][0][0]+arr3[1][1][1]
    GT cost: 0.00939548    sys cost: 3.484e-06    rate: 2696.75    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]
    GT cost: 0.0131847    sys cost: 5.884e-06    rate: 2240.77    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]
    GT cost: 0.0180965    sys cost: 7.284e-06    rate: 2484.42    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]+arr3[4][4][4]
    Program ended with exit code: 0
