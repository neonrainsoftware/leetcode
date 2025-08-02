public class Solution_38
{
	public string CountAndSay(int n)
	{
		if (n <= 1) return n.ToString();            //checks base case
		return MakePairs(n, "1");
	}

	public string MakePairs(int n, string str)
	{
		if (n <= 1) return str;                     //ends recursion (dont forget this!)
		StringBuilder sb = new();

		for (int i = 0; i < str.Length; i++)
		{
			int cnter = 1;                          //use this to keep track of amount of a digit in string
			char digit = str[i];                    //keeping track of current char

			while (i + 1 < str.Length && str[i] == str[i + 1])
			{
				cnter++;                            //while we still havent found new digit
				i++;                                //incremeent both where we are and the cnter
			}
			sb.Append(cnter).Append(digit);         //add results to new string
		}
		return MakePairs(n - 1, sb.ToString());     //recursive call with new number and string
	}
}

class SolutionClassMain
{
	static void Main(string[] args)
	{
		//Problem 38: Return the nth element of any count-and-say sequence
	}
}