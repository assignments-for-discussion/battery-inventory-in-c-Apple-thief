#include <stdio.h>
#include <assert.h>
// Using healthy,exchange and failed from the original given code.
struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
  struct CountsBySoH counts = {0, 0, 0};

  // Assuming rated capacity is always 120 Ah
  const double ratedCapacity = 120.0;

  for (int i = 0; i < nBatteries; i++) {
    // Calculate SoH for each battery
    double soh = 100.0 * presentCapacities[i] / ratedCapacity;

    // Classify batteries based on SoH
    if (soh > 80.0) {
      counts.healthy++;
    } else if (soh >= 63.0) {
      counts.exchange++;
    } else {
      counts.failed++;
    }
  }

  return counts;
}

void testBucketingByHealth() {
  // Test case 1: All batteries healthy
  const int presentCapacities1[] = {120, 118, 119, 115};
  const int numberOfBatteries1 = sizeof(presentCapacities1) / sizeof(presentCapacities1[0]);
  struct CountsBySoH counts1 = countBatteriesByHealth(presentCapacities1, numberOfBatteries1);
  assert(counts1.healthy == 4);
  assert(counts1.exchange == 0);
  assert(counts1.failed == 0);

  // Test case 2: Mix of healthy, exchange, and failed batteries
  const int presentCapacities2[] = {115, 118, 80, 95, 91, 72};
  const int numberOfBatteries2 = sizeof(presentCapacities2) / sizeof(presentCapacities2[0]);
  struct CountsBySoH counts2 = countBatteriesByHealth(presentCapacities2, numberOfBatteries2);
  assert(counts2.healthy == 2);
  assert(counts2.exchange == 3);
  assert(counts2.failed == 1);

  // Test case 3: All batteries failed
  const int presentCapacities3[] = {50, 45, 30, 20};
  const int numberOfBatteries3 = sizeof(presentCapacities3) / sizeof(presentCapacities3[0]);
  struct CountsBySoH counts3 = countBatteriesByHealth(presentCapacities3, numberOfBatteries3);
  assert(counts3.healthy == 0);
  assert(counts3.exchange == 0);
  assert(counts3.failed == 4);

  // Test case 4: Boundary case - empty array
  const int presentCapacities4[] = {};
  const int numberOfBatteries4 = 0;
  struct CountsBySoH counts4 = countBatteriesByHealth(presentCapacities4, numberOfBatteries4);
  assert(counts4.healthy == 0);
  assert(counts4.exchange == 0);
  assert(counts4.failed == 0);

  // Test case 5: Boundary case - single battery with full capacity
  const int presentCapacities5[] = {120};
  const int numberOfBatteries5 = 1;
  struct CountsBySoH counts5 = countBatteriesByHealth(presentCapacities5, numberOfBatteries5);
  assert(counts5.healthy == 1);
  assert(counts5.exchange == 0);
  assert(counts5.failed == 0);
  printf("given test cases passed\n");
}

int main() {
  testBucketingByHealth();
  return 0;
}
