/**
 * @param {string[]} arr
 * @param {number} k
 * @return {string}
 */
var kthDistinct = function(arr, k) {
    freqMap={}
    for(let str of arr){
        if(freqMap[str]) freqMap[str]++
        else freqMap[str]=1
    }
    const distArray=[]
    for(let key in freqMap){
        if(freqMap[key] < 2){
            distArray.push(key)
        }
    }
    return (distArray[k-1])?(distArray[k-1]):""
};
