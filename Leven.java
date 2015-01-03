public class Leven
{
    public static int Levenshtein(String s0, String s1)
    {
        int s0_len = s0.length() + 1;
        int s1_len = s1.length() + 1;

        int[] cost = new int[s0_len];
        int[] new_cost = new int[s0_len];

        for (int i = 0; i < s0_len; i++)
            cost[i] = i;

        try {

            for (int j = 1; j < s1_len; j++)
            {
                new_cost[0] = j;
                for (int i = 1; i < s0_len; i++)
                {
                    int match = (s0.charAt(i-1) == s1.charAt(j-1)) ? 0 : 1;

                    int cost_replace = cost[i-1] + match;
                    int cost_insert = cost[i] + 1;
                    int cost_delete = new_cost[i-1] + 1;

                    new_cost[i] = Math.min(
                        Math.min(
                            cost_insert, 
                            cost_delete), 
                        cost_replace);
                }
                int[] swap = cost; cost = new_cost; new_cost = swap;
            }

            return cost[s0_len-1];
        } catch (StringIndexOutOfBoundsException e) {
        	System.out.println(e.getMessage());
            return -1;
        }
    }

    public static void main(String[] args)
    {
        String[] compareString = { "he", "she", "his", "hers" };
        for (int i = 0; i < 4; i++) {
            for (int j = i; j < 4; j++) {
                System.out.println(compareString[i]);
                System.out.println(compareString[j]);
                System.out.println(Levenshtein(compareString[i],
                                               compareString[j]));
            }
        }
    }
}
