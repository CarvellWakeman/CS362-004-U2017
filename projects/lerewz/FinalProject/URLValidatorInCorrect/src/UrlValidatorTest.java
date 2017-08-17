/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;

import java.util.ArrayList;
import java.util.List;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }


    // Manual testing - Dustin Jun-Hin Lee
    public void testManualTest()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        int size = 15;
        String[] urls = new String[size];

        urls[0] = "http://www.amazon.com";
        urls[1] = "http://////www.google.com";
        urls[2] = "http://www.testsite.org/?username=dustin";
        urls[3] = "http://www.google.com/api/user";
        urls[4] = "google.com";
        urls[5] = "http://www.google.uk/";
        urls[6] = "http://www.google.com:8080";
        urls[7] = "http://www.google.com:65536";
        urls[8] = "https://www.google.com:65535";
        urls[9] = "http//:amazon.com";
        urls[10] = "http://www.google.org:0";
        urls[11] = "http://www.google.com:32";
        urls[12] = "xtp//www.google.com";
        urls[13] = "https://www.google.com:3332/?test=testing";
        urls[14] = "http://www.google.com:89/nom/test/dustin/abc/";

        for (int i = 0; i < size; i++) {
            System.out.println(urls[i] + " - " + urlVal.isValid(urls[i]));
        }

    }


    // Input partitioning - Matthew Fry
    public void testSchemePartition()
    {
        UrlValidator urlVal = new UrlValidator();

        String[] validSchemes = {"http://", "https://", "ftp://"};
        String[] inValidSchemes = {"http:/", "http//", "://"};
        String endTestUrl = "www.amazon.com";
        int failCount = 0;

        System.out.println("\nTesting Scheme Partition");
        System.out.println("==========================");
        for(int i = 0; i<validSchemes.length; i++) {
            String testUrl = validSchemes[i] + endTestUrl;
            if (urlVal.isValid(testUrl) != true) {
                System.out.println(testUrl + " was invalid. Expected to be valid");
                failCount++;
            }
        }
        for(int i = 0; i<inValidSchemes.length; i++) {
            String testUrl = inValidSchemes[i] + endTestUrl;
            if (urlVal.isValid(testUrl) != false) {
                System.out.println(testUrl + " was valid. Expected to be invalid");
                failCount++;
            }
        }
        if(failCount == 0) {
            System.out.println("ALL PASSED");
        }
        else {
            System.out.println(failCount + " TESTS FAILED");
        }
    }

    public void testAuthorityPartition()
    {
        UrlValidator urlVal = new UrlValidator();

        String[] validAuthoritys = {"www.amazon.com", "amazon.com", "www.amazon.co.uk", "0.0.0.0"};
        String[] inValidAuthoritys = {"1.2.3", "site.1ksj", "site.", ".com", ""};
        String begTestUrl = "http://";
        int failCount = 0;

        System.out.println("\nTesting Authority Partition");
        System.out.println("==========================");
        for(int i = 0; i<validAuthoritys.length; i++) {
            String testUrl = begTestUrl + validAuthoritys[i];
            if (urlVal.isValid(testUrl) != true) {
                System.out.println(testUrl + " was invalid. Expected to be valid");
                failCount++;
            }
        }
        for(int i = 0; i<inValidAuthoritys.length; i++) {
            String testUrl = begTestUrl + inValidAuthoritys[i];
            if (urlVal.isValid(testUrl) != false) {
                System.out.println(testUrl + " was valid. Expected to be invalid");
                failCount++;
            }
        }
        if(failCount == 0) {
            System.out.println("ALL PASSED");
        }
        else {
            System.out.println(failCount + " TESTS FAILED");
        }
    }

    public void testPortPartition()
    {
        UrlValidator urlVal = new UrlValidator();

        String[] validPort = {":80", ":12345", ""};
        String[] inValidPort = {":abc", ":-123"};
        String begTestUrl = "http://www.amazon.com";
        int failCount = 0;

        System.out.println("\nTesting Port Partition");
        System.out.println("==========================");
        for(int i = 0; i<validPort.length; i++) {
            String testUrl = begTestUrl + validPort[i];
            if (urlVal.isValid(testUrl) != true) {
                System.out.println(testUrl + " was invalid. Expected to be valid");
                failCount++;
            }
        }
        for(int i = 0; i<inValidPort.length; i++) {
            String testUrl = begTestUrl + inValidPort[i];
            if (urlVal.isValid(testUrl) != false) {
                System.out.println(testUrl + " was valid. Expected to be invalid");
                failCount++;
            }
        }
        if(failCount == 0) {
            System.out.println("ALL PASSED");
        }
        else {
            System.out.println(failCount + " TESTS FAILED");
        }
    }

    public void testPathPartition()
    {
        UrlValidator urlVal = new UrlValidator();

        String[] validPath = {"/path", "/path/path2", "/123", ""};
        String[] inValidPath = {"//path", "/path//path2", "/.."};
        String begTestUrl = "http://www.amazon.com";
        int failCount = 0;

        System.out.println("\nTesting Path Partition");
        System.out.println("==========================");
        for(int i = 0; i<validPath.length; i++) {
            String testUrl = begTestUrl + validPath[i];
            if (urlVal.isValid(testUrl) != true) {
                System.out.println(testUrl + " was invalid. Expected to be valid");
                failCount++;
            }
        }
        for(int i = 0; i<inValidPath.length; i++) {
            String testUrl = begTestUrl + inValidPath[i];
            if (urlVal.isValid(testUrl) != false) {
                System.out.println(testUrl + " was valid. Expected to be invalid");
                failCount++;
            }
        }
        if(failCount == 0) {
            System.out.println("ALL PASSED");
        }
        else {
            System.out.println(failCount + " TESTS FAILED");
        }
    }

    public void testQueryPartition()
    {
        UrlValidator urlVal = new UrlValidator();

        String[] validQuery = {"?param=val", "?param=val&param2=val2", ""};
        String[] inValidQuery = {};
        String begTestUrl = "http://www.amazon.com/";
        int failCount = 0;

        System.out.println("\nTesting Query Partition");
        System.out.println("==========================");
        for(int i = 0; i<validQuery.length; i++) {
            String testUrl = begTestUrl + validQuery[i];
            if (urlVal.isValid(testUrl) != true) {
                System.out.println(testUrl + " was invalid. Expected to be valid");
                failCount++;
            }
        }
        for(int i = 0; i<inValidQuery.length; i++) {
            String testUrl = begTestUrl + inValidQuery[i];
            if (urlVal.isValid(testUrl) != false) {
                System.out.println(testUrl + " was valid. Expected to be invalid");
                failCount++;
            }
        }
        if(failCount == 0) {
            System.out.println("ALL PASSED");
        }
        else {
            System.out.println(failCount + " TESTS FAILED");
        }
    }
   

    // Unit tests - Zach Lerew
    public void testAnyOtherUnitTest() {
        // Data structures
        List<ResultPair> SchemeTests = new ArrayList<>();
        List<ResultPair> AuthorityTests = new ArrayList<>();
        List<ResultPair> PortTests = new ArrayList<>();
        List<ResultPair> PathTests = new ArrayList<>();
        List<ResultPair> QueryTests = new ArrayList<>();

        List<List<ResultPair>> CombinedTests = new ArrayList<>();
        List<String> FailedTests = new ArrayList<>();

        // Test data with correctness flag
        SchemeTests.add(new ResultPair("http://", true));
        SchemeTests.add(new ResultPair("https://", true));
        SchemeTests.add(new ResultPair("4j:/", false));
        SchemeTests.add(new ResultPair(":", false));

        AuthorityTests.add(new ResultPair("www.reddit.com", true));
        AuthorityTests.add(new ResultPair("www.stackoverflow.com", true));
        AuthorityTests.add(new ResultPair("50.138.19.27", true));
        AuthorityTests.add(new ResultPair("BARD", false));
        AuthorityTests.add(new ResultPair("123.233.80.257", false));

        PortTests.add(new ResultPair(":80", true));
        PortTests.add(new ResultPair(":5000", true));
        PortTests.add(new ResultPair(":25565", true));
        PortTests.add(new ResultPair("80", false));
        PortTests.add(new ResultPair(":123456", false));

        PathTests.add(new ResultPair("/sources", true));
        PathTests.add(new ResultPair("", true));
        PathTests.add(new ResultPair("/recent docs", false));
        PathTests.add(new ResultPair("//nope//", false));

        QueryTests.add(new ResultPair("?user=43fGx3h", true));
        QueryTests.add(new ResultPair("?type=edited&size=small&user=john%smith", true));
        QueryTests.add(new ResultPair("", true));
        QueryTests.add(new ResultPair("?badquery==bad", false));
        QueryTests.add(new ResultPair("?close=but not close%enough", false));

        // Add URL segments to groups list
        CombinedTests.add(SchemeTests);
        CombinedTests.add(AuthorityTests);
        CombinedTests.add(PortTests);
        CombinedTests.add(PathTests);
        CombinedTests.add(QueryTests);

        Integer[] TestIndexes = new Integer[]{0,0,0,0,0};
        Integer[] TestMaxes = new Integer[]{SchemeTests.size(), AuthorityTests.size(), PortTests.size(), PathTests.size(), QueryTests.size()};


        // Create a URLValidator
        UrlValidator urlValidator = new UrlValidator();


        // Iterate through all combinations of the above data and pass it through URLValidator.isValid()
        do {
            // Build test URL and find its validity
            StringBuilder sb = new StringBuilder();
            boolean valid = true;
            for (int i = 0; i < TestIndexes.length; i++) {
                List<ResultPair> testGroup = CombinedTests.get(i);
                ResultPair test = testGroup.get(TestIndexes[i]);
                sb.append(test.item);
                valid &= test.valid;
            }

            // Run test
            if (urlValidator.isValid(sb.toString()) != valid){
                FailedTests.add(sb.toString());
            }

            // Increment URL indexes to combine
            TestIndexes = IncrementIndexes(TestIndexes, TestMaxes);
        } while (TestIndexes != null);

        // Print results
        for (String failedTest : FailedTests){
            System.out.printf("Failed Test:'%s'\n", failedTest);
        }

    }

    Integer[] IncrementIndexes(Integer[] TestIndexes, Integer[] MAXES){
        TestIndexes[TestIndexes.length - 1]++;

        for (int i = TestIndexes.length-1; i >= 0 ; i--){
            if (TestIndexes[i]+1 > MAXES[i]){
                if (i==0){
                    return null;
                }
                TestIndexes[i-1] += 1;
                TestIndexes[i] = 0;
            }
        }

        return TestIndexes;
    }


    // Run tests
    public static void main(String [ ] args) {
        UrlValidatorTest test = new UrlValidatorTest("Final Project part B");

        System.out.println("\n*** MANUAL TESTING ***\n");
        test.testManualTest();

        System.out.println("\n*** INPUT PARTITIONING TESTING ***\n");
        test.testSchemePartition();
        test.testAuthorityPartition();
        test.testPortPartition();
        test.testPathPartition();
        test.testQueryPartition();

        System.out.println("\n*** UNIT TESTING ***\n");
        test.testAnyOtherUnitTest();
    }

   

}
