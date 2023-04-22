package TestingWithJUnit;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class TestActivityThree {
    @Test
    public void TestPiThread () throws InterruptedException {
        ActivityThree actThree = new ActivityThree(2, 10);
        assertEquals(Math.PI, actThree.getPi(), 0.1);

        ActivityThree actThreeTestTwo = new ActivityThree(2, 100);
        assertEquals(Math.PI, actThreeTestTwo.getPi(), 0.01);

        ActivityThree actThreeTestThree = new ActivityThree(4, 10000);
        assertEquals(Math.PI, actThreeTestThree.getPi(), 0.0001);
    }
}
