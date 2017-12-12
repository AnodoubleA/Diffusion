//
// Created by Angel on 2017/12/10.
//

#ifndef DIFFUSION_MERSENNETWISTERENGINE_H
#define DIFFUSION_MERSENNETWISTERENGINE_H

#include <memory.h>
#include <stdexcept>
#include "../RandomEngine.h"

namespace lc {

    /**
     ** This code was modestly modified and completely reformatted, by Kent
     ** Paul Dolan, from published code.  See accompanying file
     ** TravellerDoc.html for details, credits, and status of the
     ** modifications for your use.
     */

    /**
     ** Because my opinions are brittle as old glass, and the last time they
     ** were flexible, I was still teething, this code has been reformatted
     ** to a coding style I like better and can read with eyes trained on
     ** Pascal and Fortran.  Except for commenting out the main routine
     ** included for testing, there shouldn't be any substantive changes,
     ** just whitespace changes, comment style changes, and optional brackets
     ** optioned-in wherever I caught them.  KPD.
     **
     ** Oops.  Now there are.  I added extra routines to match the ones in
     ** Scott Robert Ladd's "Randomizer" class.
     **
     ** I also provided the option to use the MersenneTwister as a Design
     ** Pattern "Solitary", with two getTwister accessor methods that create
     ** an instance only once, and a static member to hold the soliton, so
     ** that MersenneTwister as a class can own its own only instance, and
     ** thus remove the need for consumers to pass around a solitary instance
     ** as parameters or with accessor methods in creators for consumers.  By
     ** not making the constructors private, I left this as an option up to
     ** the self discipline of the programmer(s), rather than making such
     ** usage mandatory.
     */


    /**
     ** <h3>Mersenne Twister and MersenneTwisterFast</h3>
     **
     ** <p>
     * <b>Version 3</b>, based on version MT199937(99/10/29) of the Mersenne Twister
     * algorithm found at <a href="http://www.math.keio.ac.jp/matumoto/emt.html">The
     * Mersenne Twister Home Page</a>. By Sean Luke, June 2000.
     **
     ** <p>
     * <b>MersenneTwister</b> is a drop-in subclass replacement for
     * java.util.Random. It is properly synchronized and can be used in a
     * multithreaded environment.
     **
     ** <p>
     * <b>MersenneTwisterFast</b> is not a subclass of java.util.Random. It has the
     * same public methods as Random does, however, and it is algorithmically
     * identical to MersenneTwister. MersenneTwisterFast has hard-code inlined all
     * of its methods directly, and made all of them const (well, the ones of
     * consequence anyway). Further, these methods are <i>not</i> synchronized, so
     * the same MersenneTwisterFast instance cannot be shared by multiple threads.
     * But all this helps MersenneTwisterFast achieve over twice the speed of
     * MersenneTwister.
     **
     ** <h3>About the Mersenne Twister</h3>
     * <p>
     * This is a Java version of the C-program for MT19937: Integer version. The
     * MT19937 algorithm was created by Makoto Matsumoto and Takuji Nishimura, who
     * ask: "When you use this, send an email to: matumoto@math.keio.ac.jp with an
     * appropriate reference to your work". Indicate that this is a translation of
     * their algorithm into Java.
     **
     ** <p>
     * <b>Reference. </b> Makato Matsumoto and Takuji Nishimura, "Mersenne Twister:
     * A 623-Dimensionally Equidistributed Uniform Pseudo-Random Number Generator",
     * <i>ACM Transactions on Modeling and Computer Simulation,</i> Vol. 8, No. 1,
     * January 1998, pp 3--30.
     **
     ** <h3>About this Version</h3>
     * This version of the code implements the MT19937 Mersenne Twister algorithm,
     * with the 99/10/29 seeding mechanism. The original mechanism did not permit 0
     * as a seed, and odd numbers were not good seed choices. The new version
     * permits any 32-bit signed integer. This algorithm is identical to the MT19937
     * integer algorithm; real values conform to Sun's float and double random
     * number generator standards rather than attempting to implement the half-open
     * or full-open MT19937-1 and MT199937-2 algorithms.
     **
     ** <p>
     * This code is based on standard MT19937 C/C++ code by Takuji Nishimura, with
     * suggestions from Topher Cooper and Marc Rieffel, July 1997. The code was
     * originally translated into Java by Michael Lecuyer, January 1999, and is
     * Copyright (c) 1999 by Michael Lecuyer. The included license is as follows:
     * <blockquote><font size="-1">
     *
     * The basic algorithmic work of this library (appearing in nextInt() and
     * setSeed()) is free software; you can redistribute it and or modify it under
     * the terms of the GNU Library General Public License as published by the Free
     * Software Foundation; either version 2 of the License, or (at your option) any
     * later version.
     **
     ** <p>
     * This library is distributed in the hope that it will be useful, but WITHOUT
     * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
     * FOR A PARTICULAR PURPOSE. See the GNU Library General Public License for more
     * details. You should have received a copy of the GNU Library General Public
     * License along with this library; if not, write to the Free Foundation, Inc.,
     * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
     *
     * </font></blockquote>
     **
     ** <h3>Bug Fixes</h3>
     **
     ** <p>
     * This implementation implements the bug fixes made in Java 1.2's version of
     * Random, which means it can be used with earlier versions of Java. See <a
     * href=
     * "http://www.javasoft.com/products/jdk/1.2/docs/api/java/util/Random.html">
     * the JDK 1.2 java.util.Random documentation</a> for further documentation on
     * the random-number generation contracts made. Additionally, there's an
     * undocumented bug in the JDK java.util.Random.nextBytes() method, which this
     * code fixes.
     **
     ** <h3>Important Note on Seeds</h3>
     **
     ** <p>
     * Just like java.util.Random, this generator accepts a long seed but doesn't
     * use all of it. java.util.Random uses 48 bits. The Mersenne Twister instead
     * uses 32 bits (int size). So it's best if your seed does not exceed the int
     * range.
     **
     ** <h3>Timings On Different Java Versions</h3>
     **
     ** <p>
     * MersenneTwister can be used reliably on JDK version 1.1.5 or above. Earlier
     * Java versions have serious bugs in java.util.Random; only MersenneTwisterFast
     * (and not MersenneTwister nor java.util.Random) should be used with them. And
     * why would you use 'em anyway? They're very slow, as you'll see. Here are some
     * timings in milliseconds on a Sun Creator3D/Ultra 60 running SunOS 5.6.
     **
     ** <dl>
     ** <dt><i>Standard C Version (gcc -O2)</i>
     ** <dd>1070
     **
     ** <dt><i>Standard C Version (Solaris cc -O)</i>
     ** <dd>1210
     **
     ** <dd>MTF: 71640, MT: 66176, java.util.Random: 67269 <br>
     *
     * <i>Important note:</i> Do not MersenneTwister.java or java.util.Random on a
     * Java version this early! Random number generation in versions less than 1.1.5
     * has serious bugs.
     * </dl>
     *
     * @version 3
     */
    class MersenneTwisterEngine : public RandomEngine {

        /*
         * * Turn this into a soliton; there's no real need to have more than one*
         * instance, and having it own its own only instance decouples it from*
         * instantiating routines, making it much easier to share.
         */

    private:
        // Period parameters
        static const int N = 624;
        static const int M = 397;
        static const int MATRIX_A = 0x9908b0df; // private static const *
        // constant vector a
        static const int UPPER_MASK = 0x80000000; // most significant w-r
        // bits
        static const int LOWER_MASK = 0x7fffffff; // least significant r
        // bits

        // Tempering parameters
        static const int TEMPERING_MASK_B = 0x9d2c5680;
        static const int TEMPERING_MASK_C = 0xefc60000;

        // #define TEMPERING_SHIFT_U(y) (y >>> 11)
        // #define TEMPERING_SHIFT_S(y) (y << 7)
        // #define TEMPERING_SHIFT_T(y) (y << 15)
        // #define TEMPERING_SHIFT_L(y) (y >>> 18)

        int mt[]; // the array for the state vector
        int mti; // mti==N+1 means mt[N] is not initialized
        int mag01[];

        // a good initial seed (of int size, though stored in a long)
        static const long GOOD_SEED = 4357;

    public:
        ~MersenneTwisterEngine() {
            delete[] mt;
            delete[] mag01;
        }

        MersenneTwisterEngine() {
            mt = new int[N];
            mti = N;
            // mag01[x] = x * MATRIX_A for x=0,1
            mag01 = new int[2];
            mag01[0] = 0x0;
            mag01[1] = MATRIX_A;
        }

        /*
         * An alternative, more complete, method of seeding the pseudo random*
         * number generator. array must be an array of 624 ints, and they* can be
         * any value as long as they're not *all* zero.
         */
        void seed(byte array[], int length) override {
            int round = length & 3;
            for (int i = 0, j = 0; i < round; i++, j += 4) {
                mt[i] = array[j + 0] << 24;
                mt[i] = array[j + 1] << 16;
                mt[i] = array[j + 2] << 8;
                mt[i] = array[j + 3] << 0;
            }
        }

        void next(byte buf[], int len) override {
            int size = len;
            for (int x = 0; x < size; x++) {
                buf[x] = (byte) next(8);
            }
        }

        byte next() override {

            return (byte) next(8);
        }

        int needSeed() override {

            return N << 2;
        }

    protected:

        /*
         * * Returns an integer with <i>bits</i> bits filled with a random* number.
         */
        int next(int bits) {

            int r;

            if (mti >= N) // generate N words at one time
            {

                int i;

                for (i = 0; i < N - M; i++) {

                    r = (mt[i] & UPPER_MASK) | (mt[i + 1] & LOWER_MASK);
                    mt[i] = mt[i + M] ^ (r >> 1) ^ mag01[r & 0x1];

                }

                for (; i < N - 1; i++) {

                    r = (mt[i] & UPPER_MASK) | (mt[i + 1] & LOWER_MASK);
                    mt[i] = mt[i + (M - N)] ^ (r >> 1) ^ mag01[r & 0x1];

                }

                r = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
                mt[N - 1] = mt[M - 1] ^ (r >> 1) ^ mag01[r & 0x1];

                mti = 0;

            }

            r = mt[mti++];
            r ^= r >> 11; // TEMPERING_SHIFT_U(y)
            r ^= (r << 7) & TEMPERING_MASK_B; // TEMPERING_SHIFT_S(y)
            r ^= (r << 15) & TEMPERING_MASK_C; // TEMPERING_SHIFT_T(y)
            r ^= (r >> 18); // TEMPERING_SHIFT_L(y)

            return r >> (32 - bits); // hope that's right!
        }
    };
}
#endif //DIFFUSION_MERSENNETWISTERENGINE_H
