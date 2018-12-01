import java.util.ArrayList;
import java.util.List;

import javafx.util.Pair;
import junit.framework.TestCase;
import java.io.Serializable;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Collections;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
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
  private static final String URL_REGEX =
        "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?";
//        12            3  4          5       6   7        8 9
  String[] validScheme = new String[] {"http://", "ftp://", "https://", ""};
  String[] invalidScheme = new String[] {"3ht://", "http:/", "http:", "http/", "://"};

  String[] validAuthority = new String[] {"www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com"};
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
    // UrlValidatorTest t1 = new UrlValidatorTest("url tests");
    test1();
    testIsValid();
  }
  
    public void test1()
    { 
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
        //assertTrue(urlVal.isValid("http://www.google.com"));


        boolean[] resultFalse = new boolean[16];
	  	resultFalse[0] = urlVal.isValid("3ht://256.256.256.256:-1");
		resultFalse[1] = urlVal.isValid("http:/1.2.3.4.5:-1");
		resultFalse[2] = urlVal.isValid("3ht://1.2.3.4.:65636");
		resultFalse[3] = urlVal.isValid("http:/1.2.3:65636");
		resultFalse[4] = urlVal.isValid("http:.1.2.3.4");
		resultFalse[5] = urlVal.isValid("http/go.a1a/..");
		resultFalse[6] = urlVal.isValid("http:go.1aa/..");
		resultFalse[7] = urlVal.isValid("http/aaa.");
		resultFalse[8] = urlVal.isValid("://-1.0.0.0/../file"); 
		resultFalse[9] = urlVal.isValid("3ht://www.google.com:80/test1");
		resultFalse[10] = urlVal.isValid("http://1.2.3.4.5:65535/test1/");
		resultFalse[11] = urlVal.isValid("http/go.a1a/..");
		resultFalse[12] = urlVal.isValid("http:go.1aa/..");
		resultFalse[13] = urlVal.isValid("http/aaa.");
		resultFalse[14] = urlVal.isValid("3ht://1.2.3.4.:65636");
		resultFalse[15] = urlVal.isValid("http:/1.2.3:65636");
		
		int falseCount = 0;
		for (int i = 0; i < 7; i++) {
			//assertFalse(resultTrue[i]);	
			//if (resultTrue[i] == false) {falseCount++;}
		}
		for (int j = 0; j < 16; j++) {
			//assertFalse(resultFalse[j]);
			if (resultFalse[j] == true) {
				falseCount++;
				System.out.print(j + "\n");
			}
		}
		System.out.println("Num of failed cases: " + falseCount);
  }
  
// PARTITION TESTING TO COME //
  
  
    public void testIsValid()
  {
	  //create new validator object
	  UrlValidator u = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	  System.out.println("Unit Tests Start ------------");
	  
	  //preset portions of URL with expected results
	  List<Pair<String, Boolean>> scheme = new ArrayList<Pair<String,Boolean>>();
	  scheme.add(new Pair<String, Boolean>("http://", true));
	  scheme.add(new Pair<String, Boolean>("http:", false));
	  scheme.add(new Pair<String, Boolean>("", true));
	  scheme.add(new Pair<String, Boolean>("ftp://", true));
	  scheme.add(new Pair<String, Boolean>("h3t://", true));
	  scheme.add(new Pair<String, Boolean>("22://", false));

	  List<Pair<String, Boolean>> authority = new ArrayList<Pair<String,Boolean>>();
	  authority.add(new Pair<String, Boolean>("255.255.255.255", true));
	  authority.add(new Pair<String, Boolean>("0.0.0.0", true));
	  authority.add(new Pair<String, Boolean>("www.google.com", true));
	  authority.add(new Pair<String, Boolean>("go.au", true));
	  authority.add(new Pair<String, Boolean>("reddit.com", true));
	  authority.add(new Pair<String, Boolean>("256.256.256.256", false));
	  authority.add(new Pair<String, Boolean>("", false));

	  List<Pair<String, Boolean>> port = new ArrayList<Pair<String,Boolean>>();
	  port.add(new Pair<String, Boolean>("", true));
	  port.add(new Pair<String, Boolean>(":80", true));
	  port.add(new Pair<String, Boolean>(":0", true));
	  port.add(new Pair<String, Boolean>(":65a", false));
	  
	  List<Pair<String, Boolean>> queries = new ArrayList<Pair<String,Boolean>>();
	  queries.add(new Pair<String, Boolean>("?action=view", true));
	  queries.add(new Pair<String, Boolean>("?action=edit&mode=up", true));
	  queries.add(new Pair<String, Boolean>("", true));
	  
	  List<String> falsePassedUrls = new ArrayList<String>(); //if a url passes that shouldnt
	  List<String> falseFailedUrls = new ArrayList<String>(); //if a url doesnt pass that should
	  int totalTests = 0;
	  int failedTests = 0;

	  //loop through and make permutations of the given test values
	  for(int i = 0; i < scheme.size(); i++) {
		  for(int j = 0; j < authority.size(); j++) {
			  for(int k = 0; k < port.size(); k++) {
				  for(int l = 0; l < queries.size(); l++) {
					  //construct the url to test
					  String url = scheme.get(i).getKey() + authority.get(j).getKey()
							  		+ port.get(k).getKey() + queries.get(l).getKey();
					  
					  //expected result
					  boolean expected = scheme.get(i).getValue() && authority.get(j).getValue()
							  				&& port.get(k).getValue() && queries.get(l).getValue(); 

					  //test the url
					  boolean result = u.isValid(url);
					  
					  if(result != expected) {
						  if(expected) {
							  falseFailedUrls.add(url);
						  }
						  
						  else {
							  falsePassedUrls.add(url);
						  }
					  }
					  
					  totalTests++;
				  }
			  }
		  }
	  }
	  
	  System.out.println("Total tests: " + totalTests);
	  System.out.println("Bad URL's passed: " + falsePassedUrls.size());
  	  for(String a: falsePassedUrls) {
  		  System.out.println("  " + a);
  	  }
  		  
	  System.out.println();

	  System.out.println("Good URL's failed: " + falseFailedUrls.size());
	  for(String b: falseFailedUrls) {
		  System.out.println("  " + b);
	  }
	  
	  System.out.println();
	  System.out.println("Unit Tests End --------------\n");
  }
  
  
  
  public void test2()
  {
	  
  }
  public void test3(){ 
  }
 
  public void test4(){
  }
  public void test5(){
  }
  
  
  
  
}