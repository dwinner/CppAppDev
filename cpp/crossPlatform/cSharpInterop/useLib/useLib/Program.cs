using System.Runtime.InteropServices;

Console.WriteLine("Written by C#.");
var result = functionInDLL("Some string from C#.");
Console.WriteLine("C++ returned the value " + result);

return;

[DllImport("cppLib.dll", CharSet = CharSet.Unicode)]
static extern int functionInDLL(string str);