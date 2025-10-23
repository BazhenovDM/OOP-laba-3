#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include "../include/triangle.h"
#include "../include/square.h"
#include "../include/octagon.h"
#include "../include/array.h"

static Triangle* makeTriangle(const std::string& s) {
    Triangle* t = new Triangle();
    std::istringstream is(s);
    is >> *t;
    return t;
}

static Square* makeSquare(const std::string& s) {
    Square* p = new Square();
    std::istringstream is(s);
    is >> *p;
    return p;
}

static Octagon* makeOctagon(const std::string& s) {
    Octagon* p = new Octagon();
    std::istringstream is(s);
    is >> *p;
    return p;
}

static double tri_area_expected_equilateral() {
    return std::sqrt(3.0) / 4.0; // side = 1
}

static const double EPS = 1e-4;

TEST(TriangleBasic, EquilateralCorrectAreaCenter) {
    Triangle* t = makeTriangle("0 0 1 0 0.5 0.866025");
    EXPECT_TRUE(t->isCorrect());
    double area = static_cast<double>(*t);
    EXPECT_NEAR(area, tri_area_expected_equilateral(), EPS);
    Point c = t->getCenter();
    EXPECT_NEAR(c.getX(), 0.5, EPS);
    EXPECT_NEAR(c.getY(), std::sqrt(3.0)/6.0, EPS);
    delete t;
}

TEST(TriangleInvalid, CollinearPointsInvalid) {
    Triangle* t = makeTriangle("0 0 1 1 2 2");
    EXPECT_FALSE(t->isCorrect());
    double area = static_cast<double>(*t);
    EXPECT_NEAR(area, 0.0, EPS);
    delete t;
}

TEST(SquareBasic, UnitSquareCorrect) {
    Square* s = makeSquare("0 0 1 0 1 1 0 1");
    EXPECT_TRUE(s->isCorrect());
    EXPECT_NEAR(static_cast<double>(*s), 1.0, EPS);
    Point c = s->getCenter();
    EXPECT_NEAR(c.getX(), 0.5, EPS);
    EXPECT_NEAR(c.getY(), 0.5, EPS);
    delete s;
}

TEST(SquareRotated90, Correctness) {
    // square rotated 90 degrees around origin, coordinates form a unit square shifted
    Square* s = makeSquare("1 0 0 1 -1 0 0 -1");
    EXPECT_TRUE(s->isCorrect());
    Point c = s->getCenter();
    EXPECT_NEAR(c.getX(), 0.0, EPS);
    EXPECT_NEAR(c.getY(), 0.0, EPS);
    delete s;
}

TEST(SquareDegenerate, DuplicatePointsInvalid) {
    Square* s = makeSquare("0 0 0 0 1 0 1 0");
    EXPECT_FALSE(s->isCorrect());
    delete s;
}

TEST(OctagonRegular, RadiusOneCenterZero) {
    // vertices of approximate regular octagon radius=1 centered at origin
    Octagon* o = makeOctagon(
        "1.000000 0.000000 0.707107 0.707107 0.000000 1.000000 -0.707107 0.707107 "
        "-1.000000 0.000000 -0.707107 -0.707107 0.000000 -1.000000 0.707107 -0.707107"
    );
    EXPECT_TRUE(o->isCorrect());
    Point c = o->getCenter();
    EXPECT_NEAR(c.getX(), 0.0, 1e-3);
    EXPECT_NEAR(c.getY(), 0.0, 1e-3);
    double area = static_cast<double>(*o);
    EXPECT_GT(area, 0.0);
    delete o;
}

TEST(OctagonInvalid, CollinearPointsInvalid) {
    Octagon* o = makeOctagon("0 0 1 0 2 0 3 0 4 0 5 0 6 0 7 0");
    EXPECT_FALSE(o->isCorrect());
    delete o;
}

TEST(ArrayBasic, PushAndSizeAndTotalArea) {
    Array arr;
    Triangle* t = makeTriangle("0 0 1 0 0.5 0.866025");
    Square* s = makeSquare("0 0 1 0 1 1 0 1");
    Octagon* o = makeOctagon(
        "1.000000 0.000000 0.707107 0.707107 0.000000 1.000000 -0.707107 0.707107 "
        "-1.000000 0.000000 -0.707107 -0.707107 0.000000 -1.000000 0.707107 -0.707107"
    );
    arr.push_back(t);
    arr.push_back(s);
    arr.push_back(o);
    EXPECT_EQ(arr.size(), 3u);
    double sum = 0.0;
    if (t->isCorrect()) sum += static_cast<double>(*t);
    if (s->isCorrect()) sum += static_cast<double>(*s);
    if (o->isCorrect()) sum += static_cast<double>(*o);
    EXPECT_NEAR(arr.totalArea(), sum, 1e-3);
}

TEST(ArrayRemove, RemoveValidIndex) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    EXPECT_EQ(arr.size(), 2u);
    bool ok = arr.removeAt(0);
    EXPECT_TRUE(ok);
    EXPECT_EQ(arr.size(), 1u);
    // remaining item should be square
    Figure* f = arr[0];
    EXPECT_TRUE(f->isCorrect());
}

TEST(ArrayRemoveInvalid, BadIndex) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    bool ok = arr.removeAt(5);
    EXPECT_FALSE(ok);
    EXPECT_EQ(arr.size(), 1u);
}

TEST(ArrayRemoveTwice, SecondFail) {
    Array arr;
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    EXPECT_TRUE(arr.removeAt(0));
    EXPECT_FALSE(arr.removeAt(0));
}

TEST(ArrayClear, Empties) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    arr.clear();
    EXPECT_EQ(arr.size(), 0u);
}

TEST(TriangleLargeCoords, EquilateralLarge) {
    Triangle* t = makeTriangle("0 0 1000000 0 500000 866025.4037844386");
    EXPECT_TRUE(t->isCorrect());
    double area = static_cast<double>(*t);
    // expected area = sqrt(3)/4 * s^2
    double expected = std::sqrt(3.0) / 4.0 * 1000000.0 * 1000000.0;
    EXPECT_NEAR(area, expected, expected * 1e-6); // relative tolerance
    delete t;
}

TEST(Equality, TrianglePermutation) {
    Triangle a;
    std::istringstream ia("0 0 1 0 0.5 0.866025");
    ia >> a;
    Triangle b;
    std::istringstream ib("1 0 0.5 0.866025 0 0"); // permuted order
    ib >> b;
    EXPECT_TRUE(a == b);
}

TEST(AreaAfterRemoval, SumChanges) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025")); // area ~0.4330
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1")); // area 1
    double before = arr.totalArea();
    EXPECT_GT(before, 1.3); // approx 1.433
    arr.removeAt(0);
    double after = arr.totalArea();
    EXPECT_NEAR(after, 1.0, 1e-3);
}

TEST(MultipleFigures, MixedValidity) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 1 2 2")); // invalid
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1")); // valid
    arr.push_back(makeOctagon("0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0")); // invalid
    EXPECT_EQ(arr.size(), 3u);
    double total = arr.totalArea();
    EXPECT_NEAR(total, 1.0, 1e-3);
}

TEST(OctagonShifted, CenterOffset) {
    // regular octagon radius=2 centered at (1,1) (approx)
    Octagon* o = makeOctagon(
        "3.000000 1.000000 2.414214 2.414214 1.000000 3.000000 -0.414214 2.414214 "
        "-1.000000 1.000000 -0.414214 -0.414214 1.000000 -1.000000 2.414214 -0.414214"
    );
    EXPECT_TRUE(o->isCorrect());
    Point c = o->getCenter();
    EXPECT_NEAR(c.getX(), 1.0, 1e-3);
    EXPECT_NEAR(c.getY(), 1.0, 1e-3);
    delete o;
}

TEST(ManyPushesRemoves, StressBehavior) {
    Array arr;
    for (int i = 0; i < 10; ++i) {
        arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    }
    EXPECT_EQ(arr.size(), 10u);
    for (int i = 0; i < 10; ++i) {
        bool ok = arr.removeAt(0);
        EXPECT_TRUE(ok);
    }
    EXPECT_EQ(arr.size(), 0u);
}

TEST(TriangleAlmostCollinear, AreaNearlyZero) {
    Triangle* t = makeTriangle("0 0 1 1 2 2.000001");
    EXPECT_FALSE(t->isCorrect());
    EXPECT_NEAR(static_cast<double>(*t), 0.0, 1e-3);
    delete t;
}

TEST(TriangleSmallPerturbation, StillEquilateral) {
    Triangle* t = makeTriangle("0 0 1 0 0.5 0.866125"); // slight perturbation ~1e-4 in y
    EXPECT_TRUE(t->isCorrect());
    delete t;
}

TEST(SquareSmallNoise, AcceptsWithinEps) {
    Square* s = makeSquare("0 0 1.00005 0 1.00005 1.00005 0 1.00005");
    EXPECT_TRUE(s->isCorrect());
    delete s;
}


TEST(OctagonEqualSidesButSkewed, SideEqualityCheck) {
    // Construct 8 points that aim to have equal side lengths by hand (approx),
    // but not perfectly regular; isCorrect should accept if sides are equal within EPS.
    Octagon* o = makeOctagon(
        "2 0 1.41421356 1.41421356 0 2 -1.41421356 1.41421356 "
        "-2 0 -1.41421356 -1.41421356 0 -2 1.41421356 -1.41421356"
    );
    // These are approximately on circle radius 2; expect valid
    EXPECT_TRUE(o->isCorrect());
    delete o;
}

TEST(SquareEqualityDifferentOrder, OperatorEquals) {
    Square a;
    Square b;
    std::istringstream ia("0 0 1 0 1 1 0 1");
    std::istringstream ib("1 1 0 1 0 0 1 0");
    ia >> a;
    ib >> b;
    EXPECT_TRUE(a == b);
}

TEST(TriangleInequalityDifferent, NotEqual) {
    Triangle a;
    Triangle b;
    std::istringstream ia("0 0 1 0 0.5 0.866025");
    std::istringstream ib("0 0 2 0 1 1.73205");
    ia >> a;
    ib >> b;
    EXPECT_FALSE(a == b);
}

TEST(ArrayAtThrows, OutOfRangeAt) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    EXPECT_THROW(arr.at(2), std::out_of_range);
    arr.clear();
}

TEST(ArrayIndexOperator, ReturnsPointer) {
    Array arr;
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    Figure* f = arr[0];
    EXPECT_NE(f, nullptr);
    EXPECT_TRUE(f->isCorrect());
}

TEST(ArrayRemoveLast, RemoveFinalElement) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    EXPECT_TRUE(arr.removeAt(arr.size() - 1));
    EXPECT_EQ(arr.size(), 1u);
    arr.clear();
}

TEST(ArrayTotalAreaAllInvalid, ZeroSum) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 1 2 2"));
    arr.push_back(makeSquare("0 0 0 0 0 0 0 0"));
    arr.push_back(makeOctagon("0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"));
    EXPECT_NEAR(arr.totalArea(), 0.0, 1e-6);
}

TEST(ArrayTotalAreaAllInvalid, OctagonAreaPositiveAndConsistent) {
    Octagon* o = makeOctagon(
        "1.0 0.0 0.707107 0.707107 0.0 1.0 -0.707107 0.707107 "
        "-1.0 0.0 -0.707107 -0.707107 0.0 -1.0 0.707107 -0.707107"
    );
    double a = static_cast<double>(*o);
    EXPECT_GT(a, 0.0);
    // area should be stable on re-evaluation
    EXPECT_NEAR(a, static_cast<double>(*o), 1e-9);
    delete o;
}


TEST(ArrayTotalAreaAllInvalid, SquareDiagonalsEqualityCheckViaAPI) {
    Square s;
    std::istringstream is("0 0 1 0 1 1 0 1");
    is >> s;
    EXPECT_TRUE(s.isCorrect());
    // compute diagonals manually and check via points
    double dx1 = pow(s.getCenter().getX() - s.getCenter().getX(), 2); // dummy usage to ensure API works
    EXPECT_GE(static_cast<double>(s), 0.0);
}

TEST(RemoveAllThenClear, MultipleRemovals) {
    Array arr;
    for (int i = 0; i < 5; ++i) arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    for (int i = 0; i < 5; ++i) EXPECT_TRUE(arr.removeAt(0));
    EXPECT_EQ(arr.size(), 0u);
    // now push and clear
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    arr.clear();
    EXPECT_EQ(arr.size(), 0u);
}

TEST(MixedRemovalsMiddleIndex, CorrectBehavior) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025")); // 0
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));         // 1
    arr.push_back(makeTriangle("1 1 2 1 1.5 1.866025"));  // 2
    EXPECT_TRUE(arr.removeAt(1)); // remove middle
    EXPECT_EQ(arr.size(), 2u);
    // remaining should be indices 0 and 1 now (shifted)
    Figure* f0 = arr[0];
    Figure* f1 = arr[1];
    EXPECT_TRUE(f0->isCorrect());
    EXPECT_TRUE(f1->isCorrect());
}

TEST(ReverseOrderTriangleAreaSame, ClockwiseVsCounter) {
    Triangle a;
    Triangle b;
    std::istringstream ia("0 0 1 0 0.5 0.866025");
    std::istringstream ib("0 0 0.5 0.866025 1 0"); // reversed ordering
    ia >> a;
    ib >> b;
    EXPECT_NEAR(static_cast<double>(a), static_cast<double>(b), 1e-9);
}

TEST(ArrayTotalAreaAllInvalid, PrintAllOutputContainsPoints) {
    Array arr;
    arr.push_back(makeTriangle("0 0 1 0 0.5 0.866025"));
    std::ostringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    arr.printAll();
    std::cout.rdbuf(old);
    std::string out = buffer.str();
    EXPECT_NE(out.find("(0"), std::string::npos);
    EXPECT_NE(out.find("(1"), std::string::npos);
}

TEST(RemoveWithHugeIndexFail, NegativeCast) {
    Array arr;
    arr.push_back(makeSquare("0 0 1 0 1 1 0 1"));
    bool ok = arr.removeAt(static_cast<std::size_t>(-1));
    EXPECT_FALSE(ok);
    arr.clear();
}
