#include "Tensor4.h"

namespace Forth
{
	Tensor4 Inverse(const Tensor4 &m)
	{
		// Made by my awesome bot github.com/willnode/Matrix-N-Programmer
		// TODO: Make the bot smarter again, possibly use Cross(x) operation

		float A4545 = m.eu.u * m.ev.v - m.eu.v * m.ev.u;
		float A3545 = m.eu.t * m.ev.v - m.eu.v * m.ev.t;
		float A3445 = m.eu.t * m.ev.u - m.eu.u * m.ev.t;
		float A2545 = m.eu.z * m.ev.v - m.eu.v * m.ev.z;
		float A2445 = m.eu.z * m.ev.u - m.eu.u * m.ev.z;
		float A2345 = m.eu.z * m.ev.t - m.eu.t * m.ev.z;
		float A1545 = m.eu.y * m.ev.v - m.eu.v * m.ev.y;
		float A1445 = m.eu.y * m.ev.u - m.eu.u * m.ev.y;
		float A1345 = m.eu.y * m.ev.t - m.eu.t * m.ev.y;
		float A1245 = m.eu.y * m.ev.z - m.eu.z * m.ev.y;
		float A0545 = m.eu.x * m.ev.v - m.eu.v * m.ev.x;
		float A0445 = m.eu.x * m.ev.u - m.eu.u * m.ev.x;
		float A0345 = m.eu.x * m.ev.t - m.eu.t * m.ev.x;
		float A0245 = m.eu.x * m.ev.z - m.eu.z * m.ev.x;
		float A0145 = m.eu.x * m.ev.y - m.eu.y * m.ev.x;
		float A4535 = m.et.u * m.ev.v - m.et.v * m.ev.u;
		float A3535 = m.et.t * m.ev.v - m.et.v * m.ev.t;
		float A3435 = m.et.t * m.ev.u - m.et.u * m.ev.t;
		float A2535 = m.et.z * m.ev.v - m.et.v * m.ev.z;
		float A2435 = m.et.z * m.ev.u - m.et.u * m.ev.z;
		float A2335 = m.et.z * m.ev.t - m.et.t * m.ev.z;
		float A1535 = m.et.y * m.ev.v - m.et.v * m.ev.y;
		float A1435 = m.et.y * m.ev.u - m.et.u * m.ev.y;
		float A1335 = m.et.y * m.ev.t - m.et.t * m.ev.y;
		float A1235 = m.et.y * m.ev.z - m.et.z * m.ev.y;
		float A4534 = m.et.u * m.eu.v - m.et.v * m.eu.u;
		float A3534 = m.et.t * m.eu.v - m.et.v * m.eu.t;
		float A3434 = m.et.t * m.eu.u - m.et.u * m.eu.t;
		float A2534 = m.et.z * m.eu.v - m.et.v * m.eu.z;
		float A2434 = m.et.z * m.eu.u - m.et.u * m.eu.z;
		float A2334 = m.et.z * m.eu.t - m.et.t * m.eu.z;
		float A1534 = m.et.y * m.eu.v - m.et.v * m.eu.y;
		float A1434 = m.et.y * m.eu.u - m.et.u * m.eu.y;
		float A1334 = m.et.y * m.eu.t - m.et.t * m.eu.y;
		float A1234 = m.et.y * m.eu.z - m.et.z * m.eu.y;
		float A0535 = m.et.x * m.ev.v - m.et.v * m.ev.x;
		float A0435 = m.et.x * m.ev.u - m.et.u * m.ev.x;
		float A0335 = m.et.x * m.ev.t - m.et.t * m.ev.x;
		float A0235 = m.et.x * m.ev.z - m.et.z * m.ev.x;
		float A0534 = m.et.x * m.eu.v - m.et.v * m.eu.x;
		float A0434 = m.et.x * m.eu.u - m.et.u * m.eu.x;
		float A0334 = m.et.x * m.eu.t - m.et.t * m.eu.x;
		float A0234 = m.et.x * m.eu.z - m.et.z * m.eu.x;
		float A0135 = m.et.x * m.ev.y - m.et.y * m.ev.x;
		float A0134 = m.et.x * m.eu.y - m.et.y * m.eu.x;

		float B345345 = m.et.t * A4545 - m.et.u * A3545 + m.et.v * A3445;
		float B245345 = m.et.z * A4545 - m.et.u * A2545 + m.et.v * A2445;
		float B235345 = m.et.z * A3545 - m.et.t * A2545 + m.et.v * A2345;
		float B234345 = m.et.z * A3445 - m.et.t * A2445 + m.et.u * A2345;
		float B145345 = m.et.y * A4545 - m.et.u * A1545 + m.et.v * A1445;
		float B135345 = m.et.y * A3545 - m.et.t * A1545 + m.et.v * A1345;
		float B134345 = m.et.y * A3445 - m.et.t * A1445 + m.et.u * A1345;
		float B125345 = m.et.y * A2545 - m.et.z * A1545 + m.et.v * A1245;
		float B124345 = m.et.y * A2445 - m.et.z * A1445 + m.et.u * A1245;
		float B123345 = m.et.y * A2345 - m.et.z * A1345 + m.et.t * A1245;
		float B045345 = m.et.x * A4545 - m.et.u * A0545 + m.et.v * A0445;
		float B035345 = m.et.x * A3545 - m.et.t * A0545 + m.et.v * A0345;
		float B034345 = m.et.x * A3445 - m.et.t * A0445 + m.et.u * A0345;
		float B025345 = m.et.x * A2545 - m.et.z * A0545 + m.et.v * A0245;
		float B024345 = m.et.x * A2445 - m.et.z * A0445 + m.et.u * A0245;
		float B023345 = m.et.x * A2345 - m.et.z * A0345 + m.et.t * A0245;
		float B015345 = m.et.x * A1545 - m.et.y * A0545 + m.et.v * A0145;
		float B014345 = m.et.x * A1445 - m.et.y * A0445 + m.et.u * A0145;
		float B013345 = m.et.x * A1345 - m.et.y * A0345 + m.et.t * A0145;
		float B012345 = m.et.x * A1245 - m.et.y * A0245 + m.et.z * A0145;
		float B345245 = m.ez.t * A4545 - m.ez.u * A3545 + m.ez.v * A3445;
		float B245245 = m.ez.z * A4545 - m.ez.u * A2545 + m.ez.v * A2445;
		float B235245 = m.ez.z * A3545 - m.ez.t * A2545 + m.ez.v * A2345;
		float B234245 = m.ez.z * A3445 - m.ez.t * A2445 + m.ez.u * A2345;
		float B145245 = m.ez.y * A4545 - m.ez.u * A1545 + m.ez.v * A1445;
		float B135245 = m.ez.y * A3545 - m.ez.t * A1545 + m.ez.v * A1345;
		float B134245 = m.ez.y * A3445 - m.ez.t * A1445 + m.ez.u * A1345;
		float B125245 = m.ez.y * A2545 - m.ez.z * A1545 + m.ez.v * A1245;
		float B124245 = m.ez.y * A2445 - m.ez.z * A1445 + m.ez.u * A1245;
		float B123245 = m.ez.y * A2345 - m.ez.z * A1345 + m.ez.t * A1245;
		float B345235 = m.ez.t * A4535 - m.ez.u * A3535 + m.ez.v * A3435;
		float B245235 = m.ez.z * A4535 - m.ez.u * A2535 + m.ez.v * A2435;
		float B235235 = m.ez.z * A3535 - m.ez.t * A2535 + m.ez.v * A2335;
		float B234235 = m.ez.z * A3435 - m.ez.t * A2435 + m.ez.u * A2335;
		float B145235 = m.ez.y * A4535 - m.ez.u * A1535 + m.ez.v * A1435;
		float B135235 = m.ez.y * A3535 - m.ez.t * A1535 + m.ez.v * A1335;
		float B134235 = m.ez.y * A3435 - m.ez.t * A1435 + m.ez.u * A1335;
		float B125235 = m.ez.y * A2535 - m.ez.z * A1535 + m.ez.v * A1235;
		float B124235 = m.ez.y * A2435 - m.ez.z * A1435 + m.ez.u * A1235;
		float B123235 = m.ez.y * A2335 - m.ez.z * A1335 + m.ez.t * A1235;
		float B345234 = m.ez.t * A4534 - m.ez.u * A3534 + m.ez.v * A3434;
		float B245234 = m.ez.z * A4534 - m.ez.u * A2534 + m.ez.v * A2434;
		float B235234 = m.ez.z * A3534 - m.ez.t * A2534 + m.ez.v * A2334;
		float B234234 = m.ez.z * A3434 - m.ez.t * A2434 + m.ez.u * A2334;
		float B145234 = m.ez.y * A4534 - m.ez.u * A1534 + m.ez.v * A1434;
		float B135234 = m.ez.y * A3534 - m.ez.t * A1534 + m.ez.v * A1334;
		float B134234 = m.ez.y * A3434 - m.ez.t * A1434 + m.ez.u * A1334;
		float B125234 = m.ez.y * A2534 - m.ez.z * A1534 + m.ez.v * A1234;
		float B124234 = m.ez.y * A2434 - m.ez.z * A1434 + m.ez.u * A1234;
		float B123234 = m.ez.y * A2334 - m.ez.z * A1334 + m.ez.t * A1234;
		float B045245 = m.ez.x * A4545 - m.ez.u * A0545 + m.ez.v * A0445;
		float B035245 = m.ez.x * A3545 - m.ez.t * A0545 + m.ez.v * A0345;
		float B034245 = m.ez.x * A3445 - m.ez.t * A0445 + m.ez.u * A0345;
		float B025245 = m.ez.x * A2545 - m.ez.z * A0545 + m.ez.v * A0245;
		float B024245 = m.ez.x * A2445 - m.ez.z * A0445 + m.ez.u * A0245;
		float B023245 = m.ez.x * A2345 - m.ez.z * A0345 + m.ez.t * A0245;
		float B045235 = m.ez.x * A4535 - m.ez.u * A0535 + m.ez.v * A0435;
		float B035235 = m.ez.x * A3535 - m.ez.t * A0535 + m.ez.v * A0335;
		float B034235 = m.ez.x * A3435 - m.ez.t * A0435 + m.ez.u * A0335;
		float B025235 = m.ez.x * A2535 - m.ez.z * A0535 + m.ez.v * A0235;
		float B024235 = m.ez.x * A2435 - m.ez.z * A0435 + m.ez.u * A0235;
		float B023235 = m.ez.x * A2335 - m.ez.z * A0335 + m.ez.t * A0235;
		float B045234 = m.ez.x * A4534 - m.ez.u * A0534 + m.ez.v * A0434;
		float B035234 = m.ez.x * A3534 - m.ez.t * A0534 + m.ez.v * A0334;
		float B034234 = m.ez.x * A3434 - m.ez.t * A0434 + m.ez.u * A0334;
		float B025234 = m.ez.x * A2534 - m.ez.z * A0534 + m.ez.v * A0234;
		float B024234 = m.ez.x * A2434 - m.ez.z * A0434 + m.ez.u * A0234;
		float B023234 = m.ez.x * A2334 - m.ez.z * A0334 + m.ez.t * A0234;
		float B015245 = m.ez.x * A1545 - m.ez.y * A0545 + m.ez.v * A0145;
		float B014245 = m.ez.x * A1445 - m.ez.y * A0445 + m.ez.u * A0145;
		float B013245 = m.ez.x * A1345 - m.ez.y * A0345 + m.ez.t * A0145;
		float B015235 = m.ez.x * A1535 - m.ez.y * A0535 + m.ez.v * A0135;
		float B014235 = m.ez.x * A1435 - m.ez.y * A0435 + m.ez.u * A0135;
		float B013235 = m.ez.x * A1335 - m.ez.y * A0335 + m.ez.t * A0135;
		float B015234 = m.ez.x * A1534 - m.ez.y * A0534 + m.ez.v * A0134;
		float B014234 = m.ez.x * A1434 - m.ez.y * A0434 + m.ez.u * A0134;
		float B013234 = m.ez.x * A1334 - m.ez.y * A0334 + m.ez.t * A0134;
		float B012245 = m.ez.x * A1245 - m.ez.y * A0245 + m.ez.z * A0145;
		float B012235 = m.ez.x * A1235 - m.ez.y * A0235 + m.ez.z * A0135;
		float B012234 = m.ez.x * A1234 - m.ez.y * A0234 + m.ez.z * A0134;

		float C23452345 = m.ez.z * B345345 - m.ez.t * B245345 + m.ez.u * B235345 - m.ez.v * B234345;
		float C13452345 = m.ez.y * B345345 - m.ez.t * B145345 + m.ez.u * B135345 - m.ez.v * B134345;
		float C12452345 = m.ez.y * B245345 - m.ez.z * B145345 + m.ez.u * B125345 - m.ez.v * B124345;
		float C12352345 = m.ez.y * B235345 - m.ez.z * B135345 + m.ez.t * B125345 - m.ez.v * B123345;
		float C12342345 = m.ez.y * B234345 - m.ez.z * B134345 + m.ez.t * B124345 - m.ez.u * B123345;
		float C03452345 = m.ez.x * B345345 - m.ez.t * B045345 + m.ez.u * B035345 - m.ez.v * B034345;
		float C02452345 = m.ez.x * B245345 - m.ez.z * B045345 + m.ez.u * B025345 - m.ez.v * B024345;
		float C02352345 = m.ez.x * B235345 - m.ez.z * B035345 + m.ez.t * B025345 - m.ez.v * B023345;
		float C02342345 = m.ez.x * B234345 - m.ez.z * B034345 + m.ez.t * B024345 - m.ez.u * B023345;
		float C01452345 = m.ez.x * B145345 - m.ez.y * B045345 + m.ez.u * B015345 - m.ez.v * B014345;
		float C01352345 = m.ez.x * B135345 - m.ez.y * B035345 + m.ez.t * B015345 - m.ez.v * B013345;
		float C01342345 = m.ez.x * B134345 - m.ez.y * B034345 + m.ez.t * B014345 - m.ez.u * B013345;
		float C01252345 = m.ez.x * B125345 - m.ez.y * B025345 + m.ez.z * B015345 - m.ez.v * B012345;
		float C01242345 = m.ez.x * B124345 - m.ez.y * B024345 + m.ez.z * B014345 - m.ez.u * B012345;
		float C01232345 = m.ez.x * B123345 - m.ez.y * B023345 + m.ez.z * B013345 - m.ez.t * B012345;
		float C23451345 = m.ey.z * B345345 - m.ey.t * B245345 + m.ey.u * B235345 - m.ey.v * B234345;
		float C13451345 = m.ey.y * B345345 - m.ey.t * B145345 + m.ey.u * B135345 - m.ey.v * B134345;
		float C12451345 = m.ey.y * B245345 - m.ey.z * B145345 + m.ey.u * B125345 - m.ey.v * B124345;
		float C12351345 = m.ey.y * B235345 - m.ey.z * B135345 + m.ey.t * B125345 - m.ey.v * B123345;
		float C12341345 = m.ey.y * B234345 - m.ey.z * B134345 + m.ey.t * B124345 - m.ey.u * B123345;
		float C23451245 = m.ey.z * B345245 - m.ey.t * B245245 + m.ey.u * B235245 - m.ey.v * B234245;
		float C13451245 = m.ey.y * B345245 - m.ey.t * B145245 + m.ey.u * B135245 - m.ey.v * B134245;
		float C12451245 = m.ey.y * B245245 - m.ey.z * B145245 + m.ey.u * B125245 - m.ey.v * B124245;
		float C12351245 = m.ey.y * B235245 - m.ey.z * B135245 + m.ey.t * B125245 - m.ey.v * B123245;
		float C12341245 = m.ey.y * B234245 - m.ey.z * B134245 + m.ey.t * B124245 - m.ey.u * B123245;
		float C23451235 = m.ey.z * B345235 - m.ey.t * B245235 + m.ey.u * B235235 - m.ey.v * B234235;
		float C13451235 = m.ey.y * B345235 - m.ey.t * B145235 + m.ey.u * B135235 - m.ey.v * B134235;
		float C12451235 = m.ey.y * B245235 - m.ey.z * B145235 + m.ey.u * B125235 - m.ey.v * B124235;
		float C12351235 = m.ey.y * B235235 - m.ey.z * B135235 + m.ey.t * B125235 - m.ey.v * B123235;
		float C12341235 = m.ey.y * B234235 - m.ey.z * B134235 + m.ey.t * B124235 - m.ey.u * B123235;
		float C23451234 = m.ey.z * B345234 - m.ey.t * B245234 + m.ey.u * B235234 - m.ey.v * B234234;
		float C13451234 = m.ey.y * B345234 - m.ey.t * B145234 + m.ey.u * B135234 - m.ey.v * B134234;
		float C12451234 = m.ey.y * B245234 - m.ey.z * B145234 + m.ey.u * B125234 - m.ey.v * B124234;
		float C12351234 = m.ey.y * B235234 - m.ey.z * B135234 + m.ey.t * B125234 - m.ey.v * B123234;
		float C12341234 = m.ey.y * B234234 - m.ey.z * B134234 + m.ey.t * B124234 - m.ey.u * B123234;
		float C03451345 = m.ey.x * B345345 - m.ey.t * B045345 + m.ey.u * B035345 - m.ey.v * B034345;
		float C02451345 = m.ey.x * B245345 - m.ey.z * B045345 + m.ey.u * B025345 - m.ey.v * B024345;
		float C02351345 = m.ey.x * B235345 - m.ey.z * B035345 + m.ey.t * B025345 - m.ey.v * B023345;
		float C02341345 = m.ey.x * B234345 - m.ey.z * B034345 + m.ey.t * B024345 - m.ey.u * B023345;
		float C03451245 = m.ey.x * B345245 - m.ey.t * B045245 + m.ey.u * B035245 - m.ey.v * B034245;
		float C02451245 = m.ey.x * B245245 - m.ey.z * B045245 + m.ey.u * B025245 - m.ey.v * B024245;
		float C02351245 = m.ey.x * B235245 - m.ey.z * B035245 + m.ey.t * B025245 - m.ey.v * B023245;
		float C02341245 = m.ey.x * B234245 - m.ey.z * B034245 + m.ey.t * B024245 - m.ey.u * B023245;
		float C03451235 = m.ey.x * B345235 - m.ey.t * B045235 + m.ey.u * B035235 - m.ey.v * B034235;
		float C02451235 = m.ey.x * B245235 - m.ey.z * B045235 + m.ey.u * B025235 - m.ey.v * B024235;
		float C02351235 = m.ey.x * B235235 - m.ey.z * B035235 + m.ey.t * B025235 - m.ey.v * B023235;
		float C02341235 = m.ey.x * B234235 - m.ey.z * B034235 + m.ey.t * B024235 - m.ey.u * B023235;
		float C03451234 = m.ey.x * B345234 - m.ey.t * B045234 + m.ey.u * B035234 - m.ey.v * B034234;
		float C02451234 = m.ey.x * B245234 - m.ey.z * B045234 + m.ey.u * B025234 - m.ey.v * B024234;
		float C02351234 = m.ey.x * B235234 - m.ey.z * B035234 + m.ey.t * B025234 - m.ey.v * B023234;
		float C02341234 = m.ey.x * B234234 - m.ey.z * B034234 + m.ey.t * B024234 - m.ey.u * B023234;
		float C01451345 = m.ey.x * B145345 - m.ey.y * B045345 + m.ey.u * B015345 - m.ey.v * B014345;
		float C01351345 = m.ey.x * B135345 - m.ey.y * B035345 + m.ey.t * B015345 - m.ey.v * B013345;
		float C01341345 = m.ey.x * B134345 - m.ey.y * B034345 + m.ey.t * B014345 - m.ey.u * B013345;
		float C01451245 = m.ey.x * B145245 - m.ey.y * B045245 + m.ey.u * B015245 - m.ey.v * B014245;
		float C01351245 = m.ey.x * B135245 - m.ey.y * B035245 + m.ey.t * B015245 - m.ey.v * B013245;
		float C01341245 = m.ey.x * B134245 - m.ey.y * B034245 + m.ey.t * B014245 - m.ey.u * B013245;
		float C01451235 = m.ey.x * B145235 - m.ey.y * B045235 + m.ey.u * B015235 - m.ey.v * B014235;
		float C01351235 = m.ey.x * B135235 - m.ey.y * B035235 + m.ey.t * B015235 - m.ey.v * B013235;
		float C01341235 = m.ey.x * B134235 - m.ey.y * B034235 + m.ey.t * B014235 - m.ey.u * B013235;
		float C01451234 = m.ey.x * B145234 - m.ey.y * B045234 + m.ey.u * B015234 - m.ey.v * B014234;
		float C01351234 = m.ey.x * B135234 - m.ey.y * B035234 + m.ey.t * B015234 - m.ey.v * B013234;
		float C01341234 = m.ey.x * B134234 - m.ey.y * B034234 + m.ey.t * B014234 - m.ey.u * B013234;
		float C01251345 = m.ey.x * B125345 - m.ey.y * B025345 + m.ey.z * B015345 - m.ey.v * B012345;
		float C01241345 = m.ey.x * B124345 - m.ey.y * B024345 + m.ey.z * B014345 - m.ey.u * B012345;
		float C01251245 = m.ey.x * B125245 - m.ey.y * B025245 + m.ey.z * B015245 - m.ey.v * B012245;
		float C01241245 = m.ey.x * B124245 - m.ey.y * B024245 + m.ey.z * B014245 - m.ey.u * B012245;
		float C01251235 = m.ey.x * B125235 - m.ey.y * B025235 + m.ey.z * B015235 - m.ey.v * B012235;
		float C01241235 = m.ey.x * B124235 - m.ey.y * B024235 + m.ey.z * B014235 - m.ey.u * B012235;
		float C01251234 = m.ey.x * B125234 - m.ey.y * B025234 + m.ey.z * B015234 - m.ey.v * B012234;
		float C01241234 = m.ey.x * B124234 - m.ey.y * B024234 + m.ey.z * B014234 - m.ey.u * B012234;
		float C01231345 = m.ey.x * B123345 - m.ey.y * B023345 + m.ey.z * B013345 - m.ey.t * B012345;
		float C01231245 = m.ey.x * B123245 - m.ey.y * B023245 + m.ey.z * B013245 - m.ey.t * B012245;
		float C01231235 = m.ey.x * B123235 - m.ey.y * B023235 + m.ey.z * B013235 - m.ey.t * B012235;
		float C01231234 = m.ey.x * B123234 - m.ey.y * B023234 + m.ey.z * B013234 - m.ey.t * B012234;

		float det = m.ex.x * (m.ey.y * C23452345 - m.ey.z * C13452345 + m.ey.t * C12452345 - m.ey.u * C12352345 + m.ey.v * C12342345) - m.ex.y * (m.ey.x * C23452345 - m.ey.z * C03452345 + m.ey.t * C02452345 - m.ey.u * C02352345 + m.ey.v * C02342345) + m.ex.z * (m.ey.x * C13452345 - m.ey.y * C03452345 + m.ey.t * C01452345 - m.ey.u * C01352345 + m.ey.v * C01342345) - m.ex.t * (m.ey.x * C12452345 - m.ey.y * C02452345 + m.ey.z * C01452345 - m.ey.u * C01252345 + m.ey.v * C01242345) + m.ex.u * (m.ey.x * C12352345 - m.ey.y * C02352345 + m.ey.z * C01352345 - m.ey.t * C01252345 + m.ey.v * C01232345) - m.ex.v * (m.ey.x * C12342345 - m.ey.y * C02342345 + m.ey.z * C01342345 - m.ey.t * C01242345 + m.ey.u * C01232345);

		det = 1 / det;

		Tensor4 v;
		v.ex.x = det * (m.ey.y * C23452345 - m.ey.z * C13452345 + m.ey.t * C12452345 - m.ey.u * C12352345 + m.ey.v * C12342345);
		v.ex.y = det * -(m.ex.y * C23452345 - m.ex.z * C13452345 + m.ex.t * C12452345 - m.ex.u * C12352345 + m.ex.v * C12342345);
		v.ex.z = det * (m.ex.y * C23451345 - m.ex.z * C13451345 + m.ex.t * C12451345 - m.ex.u * C12351345 + m.ex.v * C12341345);
		v.ex.t = det * -(m.ex.y * C23451245 - m.ex.z * C13451245 + m.ex.t * C12451245 - m.ex.u * C12351245 + m.ex.v * C12341245);
		v.ex.u = det * (m.ex.y * C23451235 - m.ex.z * C13451235 + m.ex.t * C12451235 - m.ex.u * C12351235 + m.ex.v * C12341235);
		v.ex.v = det * -(m.ex.y * C23451234 - m.ex.z * C13451234 + m.ex.t * C12451234 - m.ex.u * C12351234 + m.ex.v * C12341234);
		v.ey.x = det * -(m.ey.x * C23452345 - m.ey.z * C03452345 + m.ey.t * C02452345 - m.ey.u * C02352345 + m.ey.v * C02342345);
		v.ey.y = det * (m.ex.x * C23452345 - m.ex.z * C03452345 + m.ex.t * C02452345 - m.ex.u * C02352345 + m.ex.v * C02342345);
		v.ey.z = det * -(m.ex.x * C23451345 - m.ex.z * C03451345 + m.ex.t * C02451345 - m.ex.u * C02351345 + m.ex.v * C02341345);
		v.ey.t = det * (m.ex.x * C23451245 - m.ex.z * C03451245 + m.ex.t * C02451245 - m.ex.u * C02351245 + m.ex.v * C02341245);
		v.ey.u = det * -(m.ex.x * C23451235 - m.ex.z * C03451235 + m.ex.t * C02451235 - m.ex.u * C02351235 + m.ex.v * C02341235);
		v.ey.v = det * (m.ex.x * C23451234 - m.ex.z * C03451234 + m.ex.t * C02451234 - m.ex.u * C02351234 + m.ex.v * C02341234);
		v.ez.x = det * (m.ey.x * C13452345 - m.ey.y * C03452345 + m.ey.t * C01452345 - m.ey.u * C01352345 + m.ey.v * C01342345);
		v.ez.y = det * -(m.ex.x * C13452345 - m.ex.y * C03452345 + m.ex.t * C01452345 - m.ex.u * C01352345 + m.ex.v * C01342345);
		v.ez.z = det * (m.ex.x * C13451345 - m.ex.y * C03451345 + m.ex.t * C01451345 - m.ex.u * C01351345 + m.ex.v * C01341345);
		v.ez.t = det * -(m.ex.x * C13451245 - m.ex.y * C03451245 + m.ex.t * C01451245 - m.ex.u * C01351245 + m.ex.v * C01341245);
		v.ez.u = det * (m.ex.x * C13451235 - m.ex.y * C03451235 + m.ex.t * C01451235 - m.ex.u * C01351235 + m.ex.v * C01341235);
		v.ez.v = det * -(m.ex.x * C13451234 - m.ex.y * C03451234 + m.ex.t * C01451234 - m.ex.u * C01351234 + m.ex.v * C01341234);
		v.et.x = det * -(m.ey.x * C12452345 - m.ey.y * C02452345 + m.ey.z * C01452345 - m.ey.u * C01252345 + m.ey.v * C01242345);
		v.et.y = det * (m.ex.x * C12452345 - m.ex.y * C02452345 + m.ex.z * C01452345 - m.ex.u * C01252345 + m.ex.v * C01242345);
		v.et.z = det * -(m.ex.x * C12451345 - m.ex.y * C02451345 + m.ex.z * C01451345 - m.ex.u * C01251345 + m.ex.v * C01241345);
		v.et.t = det * (m.ex.x * C12451245 - m.ex.y * C02451245 + m.ex.z * C01451245 - m.ex.u * C01251245 + m.ex.v * C01241245);
		v.et.u = det * -(m.ex.x * C12451235 - m.ex.y * C02451235 + m.ex.z * C01451235 - m.ex.u * C01251235 + m.ex.v * C01241235);
		v.et.v = det * (m.ex.x * C12451234 - m.ex.y * C02451234 + m.ex.z * C01451234 - m.ex.u * C01251234 + m.ex.v * C01241234);
		v.eu.x = det * (m.ey.x * C12352345 - m.ey.y * C02352345 + m.ey.z * C01352345 - m.ey.t * C01252345 + m.ey.v * C01232345);
		v.eu.y = det * -(m.ex.x * C12352345 - m.ex.y * C02352345 + m.ex.z * C01352345 - m.ex.t * C01252345 + m.ex.v * C01232345);
		v.eu.z = det * (m.ex.x * C12351345 - m.ex.y * C02351345 + m.ex.z * C01351345 - m.ex.t * C01251345 + m.ex.v * C01231345);
		v.eu.t = det * -(m.ex.x * C12351245 - m.ex.y * C02351245 + m.ex.z * C01351245 - m.ex.t * C01251245 + m.ex.v * C01231245);
		v.eu.u = det * (m.ex.x * C12351235 - m.ex.y * C02351235 + m.ex.z * C01351235 - m.ex.t * C01251235 + m.ex.v * C01231235);
		v.eu.v = det * -(m.ex.x * C12351234 - m.ex.y * C02351234 + m.ex.z * C01351234 - m.ex.t * C01251234 + m.ex.v * C01231234);
		v.ev.x = det * -(m.ey.x * C12342345 - m.ey.y * C02342345 + m.ey.z * C01342345 - m.ey.t * C01242345 + m.ey.u * C01232345);
		v.ev.y = det * (m.ex.x * C12342345 - m.ex.y * C02342345 + m.ex.z * C01342345 - m.ex.t * C01242345 + m.ex.u * C01232345);
		v.ev.z = det * -(m.ex.x * C12341345 - m.ex.y * C02341345 + m.ex.z * C01341345 - m.ex.t * C01241345 + m.ex.u * C01231345);
		v.ev.t = det * (m.ex.x * C12341245 - m.ex.y * C02341245 + m.ex.z * C01341245 - m.ex.t * C01241245 + m.ex.u * C01231245);
		v.ev.u = det * -(m.ex.x * C12341235 - m.ex.y * C02341235 + m.ex.z * C01341235 - m.ex.t * C01241235 + m.ex.u * C01231235);
		v.ev.v = det * (m.ex.x * C12341234 - m.ex.y * C02341234 + m.ex.z * C01341234 - m.ex.t * C01241234 + m.ex.u * C01231234);

		return v;
	}
} // namespace Forth
