using System;
using System.Linq;
using System.Collections.Generic;

Console.ReadLine();
var data = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
int diff = 0;
var dict = new Dictionary<int, int>();
foreach (int x in data) {
    if (dict.ContainsKey(x)) dict[x]++;
    else dict.Add(x, 1);
}
foreach (int k in dict.Keys.ToList()) {
    while (dict[k] > 1) {
        dict[k]--;
        int key = k;
        while (dict.ContainsKey(key) && dict[key] > 0) {
            key++;
            diff++;
        }
        if (dict.ContainsKey(key)) dict[key]++;
        else dict.Add(key, 1);
    }
}
Console.WriteLine(diff);