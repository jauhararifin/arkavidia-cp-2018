import java.io.*;
import java.util.*;

class main {

	class Scan {
	    private byte[] buf=new byte[1024];    //Buffer of Bytes
	    private int index;
	    private InputStream in;
	    private int total;
	    public Scan()
	    {
	        in=System.in;
	    }
	    public int scan()throws IOException    //Scan method used to scan buf
	    {
	        if(total<0)
	        throw new InputMismatchException();
	        if(index>=total)
	        {
	            index=0;
	            total=in.read(buf);
	            if(total<=0)
	            return -1;
	        }
	        return buf[index++];
	    }
	    public int scanInt()throws IOException
	    {
	        int integer=0;
	        int n=scan();
	        while(isWhiteSpace(n))    //Removing starting whitespaces
	        n=scan();
	        int neg=1;
	        if(n=='-')                //If Negative Sign encounters
	        {
	            neg=-1;
	            n=scan();
	        }
	        while(!isWhiteSpace(n))
	        {
	            if(n>='0'&&n<='9')
	            {
	                integer*=10;
	                integer+=n-'0';
	                n=scan();
	            }
	            else throw new InputMismatchException();
	        }
	        return neg*integer;
	    }
	    private boolean isWhiteSpace(int n)
	    {
	        if(n==' '||n=='\n'||n=='\r'||n=='\t'||n==-1)
	        return true;
	        return false;
	    }
	}

	class Print{
	    private final BufferedWriter bw;
	    public Print()
	    {
	        this.bw=new BufferedWriter(new OutputStreamWriter(System.out));
	    }
	    public void print(Object object)throws IOException
	    {
	        bw.append(""+object);
	    }
	    public void println(Object object)throws IOException
	    {
	        print(object);
	        bw.append("\n");
	    }
	    public void close()throws IOException
	    {
	        bw.close();
	    }
	}

	public main() throws Exception {
		Scan scan = new Scan();
		Print print = new Print();

		int t = scan.scanInt();
		while (t-- > 0) {
			int n = scan.scanInt();
			Long mini = 2000000000L;
			Long sum = 0L;
			for (int i = 0; i < n; i++) {
				int x = scan.scanInt();
				if (x < mini)
					mini = Long.valueOf(x);
				sum += Long.valueOf(x);
			}

			print.println(sum - Long.valueOf(n) * mini);
		}
		print.close();
	}

	public static void main(String[] args) throws Exception {
		new main();
	}

}