import junit.framework.TestCase;

        // <scheme>://<authority><path>?<query> except that the port number 
        // is broken out of authority to increase the number of permutations.
        // A complete URL is composed of a scheme+authority+port+path+query,
        // all of which must be individually valid for the entire URL to be considered valid.



//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!
public class UrlValidatorTest extends TestCase {
  private final boolean printStatus = false;
  private final boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
  
  String[] validScheme = new String[] {"http://", "ftp://", "https://", ""};
  String[] invalidScheme = new String[] {"3ht://", "http:/", "http:", "http/", "://"};

  String[] validAuthority = new String[] {
    "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com"
  };
  String[] invalidAuthority = new String[] {
    "256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4",
    "go.a", "go.a1a", "go.1aa","aaa.", ".aaa", "aaa", "-1.0.0.0", "1.2.3.999"
  };

  String[] validPort = new String[] {":80", ":65535",":0", ""};
  String[] inValidPort = new String[] {":-1", ":65636", ":65a"};

  String[] validPath = new String[] {"/test1", "/t123", "/$23", "/test1/", "", "/test1/file"};
  String[] invalidPath = new String[] {"/..", "/../", "/..//file", "/test1//file"};

  String[] validPathOption = new String[] {"/test1", "/t123", "/$23", "/test1/", "", "/test1/file", 
                                           "/t123/file", "/$23/file", "/test1//file"};
  String[] invalidPathOption = new String[] {"/..", "/../", "/#", "/../file", "/..//file", "/#/file"};

  String[] validUrlQuery = new String[] {"?action=view", "?action=edit&mode=up", ""};


                                                             
  Object[] testValidUrlParts = {validScheme, validAuthority, validPort, validPath, validUrlQuery};
  Object[] testInvalidUrlParts = {invalidScheme, invalidAuthority, inValidPort, invalidPath, invalidPath, validUrlQuery};                                  
                                     
  Object[] testValidUrlPartsOptions = {validScheme, validAuthority, validPort, validPathOption, validUrlQuery};
  Object[] testInvalidUrlPartsOptions = {invalidScheme, invalidAuthority, inValidPort, invalidPath, 
                                         invalidPathOption, validUrlQuery};

  int[] testPartsIndex = {0, 0, 0, 0, 0};
  
  @Override
protected void setUp() {
 for (int index = 0; index < testPartsIndex.length - 1; index++) {
   testPartsIndex[index] = 0;
 }
}

  
  public UrlValidatorTest(String testName) {
    super(testName);
  }

    /**
    * Only used to debug the unit tests.
    * @param argv
    */
  public static void main(String[] argv) {
    UrlValidatorTest t1 = new UrlValidatorTest("url tests");
    t1.setUp();
    t1.test1();
    //fct.test2();
    //fct.test3();
    //fct.test4();
    //fct.test5();
  }

  static boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
      boolean carry = true;  //add 1 to lowest order part.
      boolean maxIndex = true;
      for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
         if (carry) {
            if (index < part.length - 1) {
               index++;
               testPartsIndex[testPartsIndexIndex] = index;
               carry = false;
            } else {
               testPartsIndex[testPartsIndexIndex] = 0;
               carry = true;
            }
         }
         maxIndex &= (index == (part.length - 1));
      }
      return (!maxIndex);
  }
  
  private String testPartsIndextoString() {
      StringBuilder carryMsg = new StringBuilder("{");
     for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
        carryMsg.append(testPartsIndex[testPartsIndexIndex]);
        if (testPartsIndexIndex < testPartsIndex.length - 1) {
           carryMsg.append(',');
        } else {
           carryMsg.append('}');
        }
     }
     return carryMsg.toString();
  }
  
  public void test1()
  { 

	UrlValidator urlVal = new UrlValidator();
	

    //UrlValidator urlVal = new UrlValidator(schemes, allowAllSchemes);
    // <scheme>://<authority><path>?<query>  
    // complete URL = scheme  +  authority  +  port  +  path  +  query                                                                  
    // begin manual testing:
    //    manually combining valid URLs and invalid URLs, 
    //    call isValid() on them 
    
	
    // 1 some test URLs with all parts being valid:
	boolean [] resultTrue = new boolean[7];
	resultTrue[0] = urlVal.isValid("http://www.google.com");
	resultTrue[0] = urlVal.isValid("http://www.google.com:80/test1");
	resultTrue[1] = urlVal.isValid("http://go.com:65535/test1/");
	resultTrue[2] = urlVal.isValid("ftp://go.au:0/test1//file");
	resultTrue[3] = urlVal.isValid("ftp://0.0.0.0/t123/file");
	resultTrue[4] = urlVal.isValid("https://255.255.255.255");
	resultTrue[5] = urlVal.isValid("https://255.com/$23?action=view");
	resultTrue[6] = urlVal.isValid("https://255.com/t123?action=edit&mode=up");
     
	
    // 2 some test URLs with all parts being invalid:
	boolean [] resultFalse = new boolean[16];
	resultFalse[0] = urlVal.isValid("3ht://256.256.256.256:-1");
	resultFalse[1] = urlVal.isValid("http:/1.2.3.4.5:-1");
	resultFalse[2] = urlVal.isValid("3ht://1.2.3.4.:65636");
	resultFalse[3] = urlVal.isValid("http:/1.2.3:65636");
	resultFalse[4] = urlVal.isValid("http:.1.2.3.4");
	resultFalse[5] = urlVal.isValid("http/go.a1a/..");
	resultFalse[6] = urlVal.isValid("http:go.1aa/..");
	resultFalse[7] = urlVal.isValid("http/aaa.");
	resultFalse[8] = urlVal.isValid("://-1.0.0.0/../file");
    
    // 3 some test URLs that has 1 part that is invalid, thus also invalid 
	resultFalse[9] = urlVal.isValid("3ht://www.google.com:80/test1");
	resultFalse[10] = urlVal.isValid("http://1.2.3.4.5:65535/test1/");
	resultFalse[11] = urlVal.isValid("ftp://go.au:-1/test1//file");
	resultFalse[12] = urlVal.isValid("ftp://0.0.0.0/..");
	resultFalse[13] = urlVal.isValid("https://255.255.255.255");
	resultFalse[14] = urlVal.isValid("https://255.com/../file?action=view");
	resultFalse[15] = urlVal.isValid("http///255.com/t123?action=edit&mode=up");   

	int falseCount = 0;
	for (int i = 0; i < 7; i++) {
		if (resultTrue[i] == false) {
			falseCount++;
		}
	}
	for (int j = 0; j < 16; j++) {
		if (resultFalse[j] == true) {
			falseCount++;
		}
	}
	System.out.println("Num of failed cases: " + falseCount);
  }
  
  
  
  public void test2()
  {
  }
  public void test3(){ 
  }
  //mroe test cases
  public void test4(){
  }
  public void test5(){
  }
  

}