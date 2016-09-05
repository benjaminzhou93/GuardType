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
    
    GT cost: 6.5673e-05    sys cost: 1.673e-06    rate: 39.2546    n=1
    GT cost: 7.7373e-05    sys cost: 2.3573e-05    rate: 3.28227    n++
    GT cost: 7.5273e-05    sys cost: 2.3073e-05    rate: 3.26238    n--
    GT cost: 5.9173e-05    sys cost: 2.1373e-05    rate: 2.76859    n+=1
    GT cost: 6.0573e-05    sys cost: 2.1773e-05    rate: 2.78202    n-=1
    GT cost: 6.0673e-05    sys cost: 2.3473e-05    rate: 2.5848    n*=1
    GT cost: 0.000113573    sys cost: 0.000120073    rate: 0.945866    n/=1
    GT cost: 0.000111873    sys cost: 9.8873e-05    rate: 1.13148    n%=1
    GT cost: 5.9373e-05    sys cost: 1.9473e-05    rate: 3.04899    n^=1
    GT cost: 6.7873e-05    sys cost: 1.9673e-05    rate: 3.45006    n<<=1
    GT cost: 6.8673e-05    sys cost: 1.9973e-05    rate: 3.43829    n>>=1
    GT cost: 6.4373e-05    sys cost: 1.373e-06    rate: 46.8849    n+1
    GT cost: 6.4673e-05    sys cost: 1.373e-06    rate: 47.1034    n-1
    GT cost: 6.6673e-05    sys cost: 2.473e-06    rate: 26.9604    n*1
    GT cost: 9.2773e-05    sys cost: 2.573e-06    rate: 36.0564    n/1
    GT cost: 8.4373e-05    sys cost: 1.873e-06    rate: 45.047    n%1
    GT cost: 6.3973e-05    sys cost: 1.373e-06    rate: 46.5936    n^1
    GT cost: 6.5273e-05    sys cost: 1.373e-06    rate: 47.5404    n&1
    GT cost: 5.0573e-05    sys cost: 1.473e-06    rate: 34.3333    ~n
    GT cost: 4.9373e-05    sys cost: 1.373e-06    rate: 35.9599    !n
    GT cost: 7.1373e-05    sys cost: 1.473e-06    rate: 48.4542    n<<1
    GT cost: 7.6373e-05    sys cost: 1.873e-06    rate: 40.7758    n>>1
    GT cost: 7.2573e-05    sys cost: 5.673e-06    rate: 12.7927    n&&1
    GT cost: 8.6673e-05    sys cost: 5.173e-06    rate: 16.7549    n||1
    GT cost: 0.000100873    sys cost: 1.973e-06    rate: 51.1267    n<1
    GT cost: 6.9473e-05    sys cost: 1.873e-06    rate: 37.0918    n>1
    GT cost: 6.9873e-05    sys cost: 1.973e-06    rate: 35.4146    n<=1
    GT cost: 6.9073e-05    sys cost: 2.773e-06    rate: 24.9091    n>=1
    GT cost: 6.8773e-05    sys cost: 2.673e-06    rate: 25.7288    n==1
    GT cost: 6.7773e-05    sys cost: 1.873e-06    rate: 36.1842    n!=1
    GT cost: 6.6273e-05    sys cost: 1.8173e-05    rate: 3.64678    n=n
    GT cost: 6.8873e-05    sys cost: 2.9273e-05    rate: 2.35278    n+=n
    GT cost: 6.7773e-05    sys cost: 2.8073e-05    rate: 2.41417    n-=n
    GT cost: 6.8973e-05    sys cost: 3.4873e-05    rate: 1.97783    n*=n
    GT cost: 0.000159873    sys cost: 4.0273e-05    rate: 3.96973    n=1;n/=n
    GT cost: 0.000173473    sys cost: 3.9873e-05    rate: 4.35064    n=1;n%=n
    GT cost: 7.8573e-05    sys cost: 3.3073e-05    rate: 2.37574    n^=n
    GT cost: 8.8673e-05    sys cost: 3.3873e-05    rate: 2.61781    n<<=n
    GT cost: 0.000127473    sys cost: 2.9273e-05    rate: 4.35463    n>>=n
    GT cost: 9.1573e-05    sys cost: 6.073e-06    rate: 15.0787    n+n
    GT cost: 7.6873e-05    sys cost: 5.973e-06    rate: 12.8701    n-n
    GT cost: 7.6973e-05    sys cost: 6.073e-06    rate: 12.6746    n*n
    GT cost: 0.000188373    sys cost: 1.1673e-05    rate: 16.1375    n=1;n/n
    GT cost: 0.000209473    sys cost: 1.9073e-05    rate: 10.9827    n=1;n%n
    GT cost: 0.000128673    sys cost: 1.0173e-05    rate: 12.6485    n^n
    GT cost: 0.000124373    sys cost: 1.0173e-05    rate: 12.2258    n&n
    GT cost: 9.3373e-05    sys cost: 6.473e-06    rate: 14.425    n<<n
    GT cost: 0.000123473    sys cost: 9.373e-06    rate: 13.1733    n>>n
    GT cost: 0.000129473    sys cost: 5.373e-06    rate: 24.097    n&&n
    GT cost: 8.0573e-05    sys cost: 8.373e-06    rate: 9.62295    n||n
    GT cost: 9.5873e-05    sys cost: 6.473e-06    rate: 14.8112    n<n
    GT cost: 0.000106973    sys cost: 1.0373e-05    rate: 10.3126    n>n
    GT cost: 9.7273e-05    sys cost: 5.973e-06    rate: 16.2855    n<=n
    GT cost: 9.1173e-05    sys cost: 6.173e-06    rate: 14.7696    n>=n
    GT cost: 0.000101273    sys cost: 6.073e-06    rate: 16.6759    n==n
    GT cost: 9.8673e-05    sys cost: 7.173e-06    rate: 13.7562    n!=n
    GT cost: 0.000144773    sys cost: 8.573e-06    rate: 16.8871    n=arr[0]
    GT cost: 0.000109373    sys cost: 2.9773e-05    rate: 3.67356    n+=arr[0]
    GT cost: 0.000101073    sys cost: 2.6973e-05    rate: 3.74719    n-=arr[0]
    GT cost: 8.3773e-05    sys cost: 3.0773e-05    rate: 2.72229    n*=arr[0]
    GT cost: 0.000135873    sys cost: 0.000101173    rate: 1.34298    arr[0]=1;n/=arr[0]
    GT cost: 0.000135073    sys cost: 9.9073e-05    rate: 1.36337    arr[0]=1;n%=arr[0]
    GT cost: 8.2673e-05    sys cost: 2.7473e-05    rate: 3.00925    n^=arr[0]
    GT cost: 9.0773e-05    sys cost: 3.4973e-05    rate: 2.59552    n<<=arr[0]
    GT cost: 0.000118973    sys cost: 3.6473e-05    rate: 3.26195    n>>=arr[0]
    GT cost: 6.9273e-05    sys cost: 6.873e-06    rate: 10.079    arr[0]+arr[0]
    GT cost: 9.3173e-05    sys cost: 5.473e-06    rate: 17.0241    n-arr[0]
    GT cost: 8.7873e-05    sys cost: 5.573e-06    rate: 15.7676    n*arr[0]
    GT cost: 0.000134773    sys cost: 9.173e-06    rate: 14.6924    arr[0]=1;n/arr[0]
    GT cost: 0.000132273    sys cost: 9.073e-06    rate: 14.5788    arr[0]=1;n%arr[0]
    GT cost: 8.7073e-05    sys cost: 5.473e-06    rate: 15.9096    n^arr[0]
    GT cost: 8.7073e-05    sys cost: 5.473e-06    rate: 15.9096    n&arr[0]
    GT cost: 3.2473e-05    sys cost: 1.773e-06    rate: 18.3153    ~arr[0]
    GT cost: 3.3973e-05    sys cost: 1.773e-06    rate: 19.1613    !arr[0]
    GT cost: 9.2773e-05    sys cost: 5.573e-06    rate: 16.6469    n<<arr[0]
    GT cost: 9.2973e-05    sys cost: 5.373e-06    rate: 17.3037    n>>arr[0]
    GT cost: 9.1373e-05    sys cost: 4.273e-06    rate: 21.3838    n&&arr[0]
    GT cost: 0.000104573    sys cost: 4.373e-06    rate: 23.9133    n||arr[0]
    GT cost: 9.3473e-05    sys cost: 6.873e-06    rate: 13.6    n<arr[0]
    GT cost: 9.5273e-05    sys cost: 5.373e-06    rate: 17.7318    n>arr[0]
    GT cost: 9.7973e-05    sys cost: 7.373e-06    rate: 13.2881    n<=arr[0]
    GT cost: 9.3273e-05    sys cost: 5.473e-06    rate: 17.0424    n>=arr[0]
    GT cost: 8.9273e-05    sys cost: 5.473e-06    rate: 16.3115    n==arr[0]
    GT cost: 8.9573e-05    sys cost: 5.673e-06    rate: 15.7894    n!=arr[0]
    GT cost: 6.4873e-05    sys cost: 1.7873e-05    rate: 3.62966    arr[0]=arr[0]
    GT cost: 3.8373e-05    sys cost: 1.9873e-05    rate: 1.93091    arr[0]++
    GT cost: 3.8773e-05    sys cost: 2.0973e-05    rate: 1.84871    arr[0]--
    GT cost: 6.9173e-05    sys cost: 2.7373e-05    rate: 2.52705    arr[0]+=arr[0]
    GT cost: 7.0073e-05    sys cost: 2.7273e-05    rate: 2.56932    arr[0]-=arr[0]
    GT cost: 6.9173e-05    sys cost: 3.1073e-05    rate: 2.22614    arr[0]*=arr[0]
    GT cost: 0.000110773    sys cost: 3.5973e-05    rate: 3.07934    arr[0]=1;arr[0]/=arr[0]
    GT cost: 0.000110673    sys cost: 3.5873e-05    rate: 3.08513    arr[0]=1;arr[0]%=arr[0]
    GT cost: 6.8473e-05    sys cost: 2.7273e-05    rate: 2.51065    arr[0]^=arr[0]
    GT cost: 7.8673e-05    sys cost: 2.7273e-05    rate: 2.88465    arr[0]<<=arr[0]
    GT cost: 9.2973e-05    sys cost: 3.1873e-05    rate: 2.91698    arr[0]>>=arr[0]
    GT cost: 5.9373e-05    sys cost: 6.573e-06    rate: 9.03286    arr[0]+arr[0]
    GT cost: 5.9073e-05    sys cost: 6.473e-06    rate: 9.12606    arr[0]-arr[0]
    GT cost: 6.0373e-05    sys cost: 6.373e-06    rate: 9.47325    arr[0]*arr[0]
    GT cost: 9.3273e-05    sys cost: 1.0473e-05    rate: 8.90604    arr[0]=1;arr[0]/arr[0]
    GT cost: 9.4973e-05    sys cost: 1.0473e-05    rate: 9.06837    arr[0]=1;arr[0]%arr[0]
    GT cost: 5.9073e-05    sys cost: 6.273e-06    rate: 9.41703    arr[0]^arr[0]
    GT cost: 5.8373e-05    sys cost: 6.273e-06    rate: 9.30544    arr[0]&arr[0]
    GT cost: 6.2873e-05    sys cost: 6.373e-06    rate: 9.86553    arr[0]<<arr[0]
    GT cost: 5.9473e-05    sys cost: 6.373e-06    rate: 9.33203    arr[0]>>arr[0]
    GT cost: 6.4673e-05    sys cost: 3.173e-06    rate: 20.3823    arr[0]&&arr[0]
    GT cost: 3.6873e-05    sys cost: 5.073e-06    rate: 7.26848    arr[0]||arr[0]
    GT cost: 6.0973e-05    sys cost: 6.373e-06    rate: 9.56739    arr[0]<arr[0]
    GT cost: 6.2073e-05    sys cost: 6.573e-06    rate: 9.44363    arr[0]>arr[0]
    GT cost: 5.9873e-05    sys cost: 6.473e-06    rate: 9.24965    arr[0]<=arr[0]
    GT cost: 6.1573e-05    sys cost: 6.373e-06    rate: 9.66154    arr[0]>=arr[0]
    GT cost: 5.9073e-05    sys cost: 6.373e-06    rate: 9.26926    arr[0]==arr[0]
    GT cost: 5.9373e-05    sys cost: 6.273e-06    rate: 9.46485    arr[0]!=arr[0]
    GT cost: 2.9773e-05    sys cost: 2.173e-06    rate: 13.7013    arr[0]=1
    GT cost: 3.2073e-05    sys cost: 2.3773e-05    rate: 1.34914    arr[0]++
    GT cost: 3.1973e-05    sys cost: 2.5073e-05    rate: 1.2752    arr[0]--
    GT cost: 3.3573e-05    sys cost: 2.3673e-05    rate: 1.4182    arr[0]+=1
    GT cost: 3.1673e-05    sys cost: 2.3773e-05    rate: 1.33231    arr[0]-=1
    GT cost: 2.6473e-05    sys cost: 2.4073e-05    rate: 1.0997    arr[0]*=1
    GT cost: 2.9473e-05    sys cost: 0.000127573    rate: 0.231029    arr[0]/=1
    GT cost: 3.2473e-05    sys cost: 0.000101973    rate: 0.318447    arr[0]%=1
    GT cost: 3.5673e-05    sys cost: 2.5473e-05    rate: 1.40042    arr[0]^=1
    GT cost: 3.1773e-05    sys cost: 2.2873e-05    rate: 1.38911    arr[0]<<=1
    GT cost: 3.1873e-05    sys cost: 2.4473e-05    rate: 1.30237    arr[0]>>=1
    GT cost: 2.7473e-05    sys cost: 2.273e-06    rate: 12.0867    arr[0]+1
    GT cost: 3.1973e-05    sys cost: 3.573e-06    rate: 8.9485    arr[0]-1
    GT cost: 4.7073e-05    sys cost: 1.0073e-05    rate: 4.67319    arr[0]*1
    GT cost: 5.3073e-05    sys cost: 7.773e-06    rate: 6.82787    arr[0]/1
    GT cost: 5.1173e-05    sys cost: 4.273e-06    rate: 11.9759    arr[0]%1
    GT cost: 3.7373e-05    sys cost: 4.573e-06    rate: 8.17253    arr[0]^1
    GT cost: 3.6273e-05    sys cost: 3.673e-06    rate: 9.87558    arr[0]&1
    GT cost: 3.4973e-05    sys cost: 4.073e-06    rate: 8.58655    arr[0]<<1
    GT cost: 3.5373e-05    sys cost: 3.073e-06    rate: 11.5109    arr[0]>>1
    GT cost: 6.2973e-05    sys cost: 6.973e-06    rate: 9.03098    arr[0]&&1
    GT cost: 4.9973e-05    sys cost: 7.973e-06    rate: 6.26778    arr[0]||1
    GT cost: 4.1373e-05    sys cost: 3.173e-06    rate: 13.0391    arr[0]<1
    GT cost: 4.0873e-05    sys cost: 3.273e-06    rate: 12.4879    arr[0]>1
    GT cost: 3.8673e-05    sys cost: 3.373e-06    rate: 11.4655    arr[0]<=1
    GT cost: 3.9373e-05    sys cost: 3.173e-06    rate: 12.4088    arr[0]>=1
    GT cost: 3.9373e-05    sys cost: 3.273e-06    rate: 12.0296    arr[0]==1
    GT cost: 3.9173e-05    sys cost: 2.173e-06    rate: 18.0272    arr[0]!=1
    GT cost: 7.2173e-05    sys cost: 1.373e-06    rate: 52.5659    1+n
    GT cost: 7.1473e-05    sys cost: 5.073e-06    rate: 14.0889    1-n
    GT cost: 7.7373e-05    sys cost: 2.073e-06    rate: 37.3242    1*n
    GT cost: 0.000189273    sys cost: 6.073e-06    rate: 31.1663    n=1;1/n
    GT cost: 0.000277573    sys cost: 9.673e-06    rate: 28.6956    n=1;1%n
    GT cost: 8.4973e-05    sys cost: 2.873e-06    rate: 29.5764    1^n
    GT cost: 7.2273e-05    sys cost: 1.373e-06    rate: 52.6387    1&n
    GT cost: 8.7173e-05    sys cost: 5.673e-06    rate: 15.3663    1<<n
    GT cost: 7.6573e-05    sys cost: 1.873e-06    rate: 40.8825    1>>n
    GT cost: 8.0473e-05    sys cost: 1.873e-06    rate: 42.9648    1&&n
    GT cost: 7.3773e-05    sys cost: 9.273e-06    rate: 7.95568    int x=1; x||n
    GT cost: 6.8173e-05    sys cost: 2.373e-06    rate: 28.7286    1<n
    GT cost: 6.7973e-05    sys cost: 1.973e-06    rate: 34.4516    1>n
    GT cost: 6.7873e-05    sys cost: 1.973e-06    rate: 34.4009    1<=n
    GT cost: 0.000100973    sys cost: 4.673e-06    rate: 21.6077    1>=n
    GT cost: 7.6773e-05    sys cost: 2.073e-06    rate: 37.0347    1==n
    GT cost: 7.7073e-05    sys cost: 4.673e-06    rate: 16.4933    1!=n
    GT cost: 2.7173e-05    sys cost: 2.573e-06    rate: 10.5608    1+arr[0]
    GT cost: 2.8773e-05    sys cost: 2.573e-06    rate: 11.1827    1-arr[0]
    GT cost: 2.7673e-05    sys cost: 2.373e-06    rate: 11.6616    1*arr[0]
    GT cost: 6.1773e-05    sys cost: 6.473e-06    rate: 9.54318    arr[0]=1;1/arr[0]
    GT cost: 5.8873e-05    sys cost: 6.373e-06    rate: 9.23788    arr[0]=1;1%arr[0]
    GT cost: 2.6773e-05    sys cost: 2.173e-06    rate: 12.3208    1^arr[0]
    GT cost: 2.7273e-05    sys cost: 2.473e-06    rate: 11.0283    1&arr[0]
    GT cost: 2.9273e-05    sys cost: 2.273e-06    rate: 12.8786    1<<arr[0]
    GT cost: 2.6873e-05    sys cost: 2.173e-06    rate: 12.3668    1>>arr[0]
    GT cost: 2.7273e-05    sys cost: 3.173e-06    rate: 8.59534    1&&arr[0]
    GT cost: 6.773e-06    sys cost: 9.373e-06    rate: 0.722607    int x=1; x||arr[0]
    GT cost: 2.9573e-05    sys cost: 2.173e-06    rate: 13.6093    1<arr[0]
    GT cost: 2.8573e-05    sys cost: 2.073e-06    rate: 13.7834    1>arr[0]
    GT cost: 2.7673e-05    sys cost: 1.773e-06    rate: 15.608    1<=arr[0]
    GT cost: 2.3973e-05    sys cost: 1.473e-06    rate: 16.2749    1>=arr[0]
    GT cost: 2.3373e-05    sys cost: 1.473e-06    rate: 15.8676    1==arr[0]
    GT cost: 2.2573e-05    sys cost: 1.673e-06    rate: 13.4925    1!=arr[0]
    GT cost: 6.7473e-05    sys cost: 5.573e-06    rate: 12.1071    l+n
    GT cost: 6.7673e-05    sys cost: 5.073e-06    rate: 13.3398    l-n
    GT cost: 6.8073e-05    sys cost: 5.073e-06    rate: 13.4187    l*n
    GT cost: 0.000239073    sys cost: 8.773e-06    rate: 27.251    n=1;l/n
    GT cost: 0.000239073    sys cost: 8.773e-06    rate: 27.251    n=1;l%n
    GT cost: 6.7473e-05    sys cost: 5.273e-06    rate: 12.7959    l^n
    GT cost: 6.7473e-05    sys cost: 5.073e-06    rate: 13.3004    l&n
    GT cost: 6.7773e-05    sys cost: 5.173e-06    rate: 13.1013    l<<n
    GT cost: 7.7073e-05    sys cost: 5.073e-06    rate: 15.1928    l>>n
    GT cost: 9.1773e-05    sys cost: 4.873e-06    rate: 18.833    l&&n
    GT cost: 6.5573e-05    sys cost: 4.573e-06    rate: 14.3392    l||n
    GT cost: 0.000160673    sys cost: 1.2373e-05    rate: 12.9858    l<n
    GT cost: 0.000133673    sys cost: 7.973e-06    rate: 16.7657    l>n
    GT cost: 0.000105273    sys cost: 9.173e-06    rate: 11.4764    l<=n
    GT cost: 0.000105473    sys cost: 7.873e-06    rate: 13.3968    l>=n
    GT cost: 0.000108973    sys cost: 7.973e-06    rate: 13.6678    l==n
    GT cost: 0.000182773    sys cost: 1.4673e-05    rate: 12.4564    l!=n
    GT cost: 0.000128373    sys cost: 1.7173e-05    rate: 7.47528    f=arr[0]
    GT cost: 0.000124973    sys cost: 3.7973e-05    rate: 3.2911    f+=arr[0]
    GT cost: 9.1073e-05    sys cost: 3.9073e-05    rate: 2.33084    f-=arr[0]
    GT cost: 8.4773e-05    sys cost: 4.3873e-05    rate: 1.93224    f*=arr[0]
    GT cost: 0.000121273    sys cost: 6.5773e-05    rate: 1.84381    arr[0]=1;f/=arr[0]
    GT cost: 9.1173e-05    sys cost: 7.573e-06    rate: 12.0392    f-arr[0]
    GT cost: 0.000101873    sys cost: 8.473e-06    rate: 12.0233    f*arr[0]
    GT cost: 0.000138973    sys cost: 1.6273e-05    rate: 8.5401    arr[0]=1;f/arr[0]
    GT cost: 2.8373e-05    sys cost: 2.673e-06    rate: 10.6147    ~arr[0]
    GT cost: 2.9573e-05    sys cost: 2.273e-06    rate: 13.0106    !arr[0]
    GT cost: 0.000124873    sys cost: 1.1273e-05    rate: 11.0772    f&&arr[0]
    GT cost: 0.000105673    sys cost: 7.073e-06    rate: 14.9403    f||arr[0]
    GT cost: 0.000108673    sys cost: 1.1373e-05    rate: 9.55535    f<arr[0]
    GT cost: 0.000114773    sys cost: 6.973e-06    rate: 16.4596    f>arr[0]
    GT cost: 9.4973e-05    sys cost: 5.473e-06    rate: 17.353    f<=arr[0]
    GT cost: 9.3673e-05    sys cost: 5.373e-06    rate: 17.434    f>=arr[0]
    GT cost: 9.8373e-05    sys cost: 5.573e-06    rate: 17.6517    f==arr[0]
    GT cost: 9.7073e-05    sys cost: 5.473e-06    rate: 17.7367    f!=arr[0]
    GT cost: 6.7573e-05    sys cost: 9.073e-06    rate: 7.4477    farr[0]=arr[0]
    GT cost: 6.9873e-05    sys cost: 3.1073e-05    rate: 2.24867    farr[0]+=arr[0]
    GT cost: 7.0873e-05    sys cost: 3.1073e-05    rate: 2.28085    farr[0]-=arr[0]
    GT cost: 7.0273e-05    sys cost: 3.8373e-05    rate: 1.83131    farr[0]*=arr[0]
    GT cost: 0.000100173    sys cost: 5.9673e-05    rate: 1.6787    arr[0]=1;farr[0]/=arr[0]
    GT cost: 6.3373e-05    sys cost: 5.473e-06    rate: 11.5792    farr[0]-arr[0]
    GT cost: 6.3473e-05    sys cost: 5.473e-06    rate: 11.5975    farr[0]*arr[0]
    GT cost: 0.000105573    sys cost: 1.0973e-05    rate: 9.62116    arr[0]=1;farr[0]/arr[0]
    GT cost: 3.9573e-05    sys cost: 2.473e-06    rate: 16.002    !farr[0]
    GT cost: 9.2673e-05    sys cost: 9.373e-06    rate: 9.88723    farr[0]&&arr[0]
    GT cost: 5.2273e-05    sys cost: 2.8473e-05    rate: 1.83588    farr[0]||arr[0]
    GT cost: 9.4773e-05    sys cost: 6.773e-06    rate: 13.9928    farr[0]<arr[0]
    GT cost: 8.2273e-05    sys cost: 1.2673e-05    rate: 6.49199    farr[0]>arr[0]
    GT cost: 6.8673e-05    sys cost: 6.573e-06    rate: 10.4477    farr[0]<=arr[0]
    GT cost: 6.8173e-05    sys cost: 6.573e-06    rate: 10.3717    farr[0]>=arr[0]
    GT cost: 6.8173e-05    sys cost: 7.873e-06    rate: 8.65909    farr[0]==arr[0]
    GT cost: 7.5473e-05    sys cost: 6.773e-06    rate: 11.1432    farr[0]!=arr[0]
    GT cost: 8.0973e-05    sys cost: 2.073e-06    rate: 39.0608    int x = arr[0]+arr[1]
    GT cost: 0.000121773    sys cost: 3.773e-06    rate: 32.2748    int x = arr[0]+arr[1]+arr[2]
    GT cost: 0.000159073    sys cost: 5.873e-06    rate: 27.0855    int x = arr[0]+arr[1]+arr[2]+arr[3]
    GT cost: 0.000209173    sys cost: 1.6073e-05    rate: 13.0139    int x = arr[0]+arr[1]+arr[2]+arr[3]+arr[4]
    GT cost: 0.000144973    sys cost: 1.973e-06    rate: 73.4785    int x = arr2[0][0]+arr2[1][1]
    GT cost: 0.000205873    sys cost: 3.973e-06    rate: 51.818    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]
    GT cost: 0.000315373    sys cost: 8.773e-06    rate: 35.9481    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]
    GT cost: 0.000452473    sys cost: 8.773e-06    rate: 51.5756    int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]+arr2[4][4]
    GT cost: 0.000408073    sys cost: 3.473e-06    rate: 117.499    int x = arr3[0][0][0]+arr3[1][1][1]
    GT cost: 0.000457873    sys cost: 5.373e-06    rate: 85.2174    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]
    GT cost: 0.000614473    sys cost: 1.3073e-05    rate: 47.0032    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]
    GT cost: 0.000949273    sys cost: 1.1073e-05    rate: 85.7286    int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]+arr3[4][4][4]
    
    
    
    
    
    
    
    
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
