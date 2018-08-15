#include <gtest/gtest.h>

#include "math/linalg/blas/base.hpp"
#include "math/linalg/blas/gemm_tn_novector.hpp"
#include "math/linalg/blas/gemm_tn_novector_threaded.hpp"
#include "math/linalg/matrix.hpp"
#include "math/linalg/prototype.hpp"

using namespace fetch;
using namespace fetch::math::linalg;

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded1)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(1), beta = type(0);

  Matrix<type> A = Matrix<type>(R"(
	0.3745401188473625 0.9507143064099162 0.7319939418114051;
 0.5986584841970366 0.15601864044243652 0.15599452033620265
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.05808361216819946 0.8661761457749352 0.6011150117432088;
 0.7080725777960455 0.020584494295802447 0.9699098521619943
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.8324426408004217 0.21233911067827616 0.18182496720710062;
 0.18340450985343382 0.3042422429595377 0.5247564316322378;
 0.43194501864211576 0.2912291401980419 0.6118528947223795
	)");

  Matrix<type> R = Matrix<type>(R"(
	0.4456482991294304 0.33674079873438223 0.8057864498423064;
 0.1656934419785827 0.8266976184734581 0.7228126579480724;
 0.15297229436215787 0.6372467595628419 0.591313169085288
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded2)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(0), beta = type(1);

  Matrix<type> A = Matrix<type>(R"(
	0.13949386065204183 0.29214464853521815 0.3663618432936917;
 0.45606998421703593 0.7851759613930136 0.19967378215835974
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.5142344384136116 0.5924145688620425 0.046450412719997725;
 0.6075448519014384 0.17052412368729153 0.06505159298527952
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.9488855372533332 0.9656320330745594 0.8083973481164611;
 0.3046137691733707 0.09767211400638387 0.6842330265121569;
 0.4401524937396013 0.12203823484477883 0.4951769101112702
	)");

  Matrix<type> R = Matrix<type>(R"(
	0.9488855372533332 0.9656320330745594 0.8083973481164611;
 0.3046137691733707 0.09767211400638387 0.6842330265121569;
 0.4401524937396013 0.12203823484477883 0.4951769101112702
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded3)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(1), beta = type(1);

  Matrix<type> A = Matrix<type>(R"(
	0.034388521115218396 0.9093204020787821 0.2587799816000169;
 0.662522284353982 0.31171107608941095 0.5200680211778108
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.5467102793432796 0.18485445552552704 0.9695846277645586;
 0.7751328233611146 0.9394989415641891 0.8948273504276488
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.5978999788110851 0.9218742350231168 0.0884925020519195;
 0.1959828624191452 0.045227288910538066 0.32533033076326434;
 0.388677289689482 0.2713490317738959 0.8287375091519293
	)");

  Matrix<type> R = Matrix<type>(R"(
	1.1302433056071457 1.5506700912834535 0.7146781438045392;
 0.9347351599342958 0.5061714427949007 1.4859210106475778;
 0.9332767593138604 0.8077890198114085 1.545017690717192
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded4)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(0.07249804430136064), beta = type(0.4959497105004812);

  Matrix<type> A = Matrix<type>(R"(
	0.3567533266935893 0.28093450968738076 0.5426960831582485;
 0.14092422497476265 0.8021969807540397 0.07455064367977082
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.9868869366005173 0.7722447692966574 0.1987156815341724;
 0.005522117123602399 0.8154614284548342 0.7068573438476171
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.7290071680409873 0.7712703466859457 0.07404465173409036;
 0.3584657285442726 0.11586905952512971 0.8631034258755935;
 0.6232981268275579 0.3308980248526492 0.06355835028602363
	)");

  Matrix<type> R = Matrix<type>(R"(
	0.38713207520673776 0.41081593073386347 0.04908376090937605;
 0.19820225410561912 0.12061906325208768 0.473212382731158;
 0.3479828503670018 0.1988996765952401 0.04316050112886288
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded5)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(0.619130592827174), beta = type(0.6518772480445368);

  Matrix<type> A = Matrix<type>(R"(
	0.3109823217156622 0.32518332202674705 0.7296061783380641 0.6375574713552131 0.8872127425763265;
 0.4722149251619493 0.1195942459383017 0.713244787222995 0.7607850486168974 0.5612771975694962;
 0.770967179954561 0.49379559636439074 0.5227328293819941 0.42754101835854963 0.02541912674409519
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.10789142699330445 0.03142918568673425 0.6364104112637804 0.3143559810763267 0.5085706911647028;
 0.907566473926093 0.24929222914887494 0.41038292303562973 0.7555511385430487 0.22879816549162246;
 0.07697990982879299 0.289751452913768 0.16122128725400442 0.9296976523425731 0.808120379564417
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.6334037565104235 0.8714605901877177 0.8036720768991145 0.18657005888603584 0.8925589984899778;
 0.5393422419156507 0.8074401551640625 0.8960912999234932 0.3180034749718639 0.11005192452767676;
 0.22793516254194168 0.4271077886262563 0.8180147659224931 0.8607305832563434 0.006952130531190703;
 0.5107473025775657 0.417411003148779 0.22210781047073025 0.1198653673336828 0.33761517140362796;
 0.9429097039125192 0.32320293202075523 0.5187906217433661 0.7030189588951778 0.363629602379294
	)");

  Matrix<type> R = Matrix<type>(R"(
	0.7357581318083051 0.7853272933922926 0.8433654725944324 0.8468134266706708 1.1323900680229741;
 0.46404168824010344 0.6397222031790877 0.7919464296623041 0.6107640377164762 0.4381343611446993;
 0.6230101866212311 0.49647958757298916 1.054124802299126 1.3376243712384948 0.5968396055785158;
 0.823396310885939 0.47862805569681477 0.6319747734666199 0.8042017931552963 0.7425146349562761;
 0.9905205692782388 0.31914276334638003 0.8329153140354394 0.9081462908129233 0.6086262804872983
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded6)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(-4.027171092605927), beta = type(-1.6435872137633112);

  Matrix<type> A = Matrix<type>(R"(
	0.9717820827209607 0.9624472949421112 0.25178229582536416;
 0.49724850589238545 0.30087830981676966 0.2848404943774676
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.036886947354532795 0.6095643339798968 0.5026790232288615;
 0.05147875124998935 0.27864646423661144 0.9082658859666537
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.23956189066697242 0.1448948720912231 0.489452760277563;
 0.9856504541106007 0.2420552715115004 0.6721355474058786;
 0.7616196153287176 0.23763754399239967 0.7282163486118596
	)");

  Matrix<type> R = Matrix<type>(R"(
	-0.6411855824449596 -3.1816882046950297 -4.590515903789576;
 -1.8253502829221928 -3.098106385057142 -4.15360235381796;
 -1.3482418815408022 -1.3282939608481885 -2.7484617952012944
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}

TEST(blas_DGEMM, blas_gemm_tn_novector_threaded7)
{

  Blas<double, Signature(_C <= _alpha, _A, _B, _beta, _C),
       Computes(_C = _alpha * T(_A) * _B + _beta * _C), platform::Parallelisation::THREADING>
      gemm_tn_novector_threaded;
  // Compuing _C = _alpha * T(_A) * _B + _beta * _C
  using type = double;

  type alpha = type(4.144711452578657), beta = type(-3.296367993313047);

  Matrix<type> A = Matrix<type>(R"(
	0.3677831327192532 0.6323058305935795 0.6335297107608947 0.5357746840747585 0.0902897700544083 0.835302495589238 0.32078006497173583 0.18651851039985423 0.040775141554763916 0.5908929431882418;
 0.6775643618422824 0.016587828927856152 0.512093058299281 0.22649577519793795 0.6451727904094499 0.17436642900499144 0.690937738102466 0.3867353463005374 0.9367299887367345 0.13752094414599325;
 0.3410663510502585 0.11347352124058907 0.9246936182785628 0.877339353380981 0.2579416277151556 0.659984046034179 0.8172222002012158 0.5552008115994623 0.5296505783560065 0.24185229090045168;
 0.09310276780589921 0.8972157579533268 0.9004180571633305 0.6331014572732679 0.3390297910487007 0.3492095746126609 0.7259556788702394 0.8971102599525771 0.8870864242651173 0.7798755458576239;
 0.6420316461542878 0.08413996499504883 0.16162871409461377 0.8985541885270792 0.6064290596595899 0.009197051616629648 0.1014715428660321 0.6635017691080558 0.005061583846218687 0.16080805141749865;
 0.5487337893665861 0.6918951976926933 0.6519612595026005 0.22426930946055978 0.7121792213475359 0.23724908749680007 0.3253996981592677 0.7464914051180241 0.6496328990472147 0.8492234104941779;
 0.6576128923003434 0.5683086033354716 0.09367476782809248 0.3677158030594335 0.26520236768172545 0.24398964337908358 0.9730105547524456 0.3930977246667604 0.8920465551771133 0.6311386259972629;
 0.7948113035416484 0.5026370931051921 0.5769038846263591 0.4925176938188639 0.1952429877980445 0.7224521152615053 0.2807723624408558 0.02431596643145384 0.6454722959071678 0.17711067940704894;
 0.9404585843529143 0.9539285770025874 0.9148643902204485 0.3701587002554444 0.015456616528867428 0.9283185625877254 0.42818414831731433 0.9666548190436696 0.9636199770892528 0.8530094554673601;
 0.2944488920695857 0.38509772860192526 0.8511366715168569 0.31692200515627766 0.1694927466860925 0.5568012624583502 0.936154774160781 0.696029796674973 0.570061170089365 0.09717649377076854
	)");

  Matrix<type> B = Matrix<type>(R"(
	0.6150072266991697 0.9900538501042633 0.14008401523652403 0.5183296523637367 0.8773730719279554 0.7407686177542044 0.697015740995268 0.7024840839871093 0.35949115121975517 0.29359184426449336;
 0.8093611554785136 0.8101133946791808 0.8670723185801037 0.9132405525564713 0.5113423988609378 0.5015162946871996 0.7982951789667752 0.6499639307777652 0.7019668772577033 0.795792669436101;
 0.8900053418175663 0.3379951568515358 0.375582952639944 0.093981939840869 0.578280140996174 0.035942273796742086 0.46559801813246016 0.5426446347075766 0.2865412521282844 0.5908332605690108;
 0.03050024993904943 0.03734818874921442 0.8226005606596583 0.3601906414112629 0.12706051265188478 0.5222432600548044 0.7699935530986108 0.21582102749684318 0.6228904758190003 0.085347464993768;
 0.0516817211686077 0.531354631568148 0.5406351216101065 0.6374299014982066 0.7260913337226615 0.9758520794625346 0.5163003483011953 0.32295647294124596 0.7951861947687037 0.2708322512620742;
 0.4389714207056361 0.07845638134226596 0.02535074341545751 0.9626484146779251 0.8359801205122058 0.695974206093698 0.4089529444142699 0.17329432007084578 0.15643704267108605 0.25024289816459533;
 0.5492266647061205 0.7145959227000623 0.6601973767177313 0.27993389694594284 0.9548652806631941 0.7378969166957685 0.5543540525114007 0.6117207462343522 0.4196000624277899 0.24773098950115746;
 0.3559726786512616 0.7578461104643691 0.014393488629755868 0.11607264050691624 0.04600264202175275 0.040728802318970136 0.8554605840110072 0.7036578593800237 0.4741738290873252 0.09783416065100148;
 0.49161587511683236 0.4734717707805657 0.17320186991001518 0.43385164923797304 0.39850473439737344 0.6158500980522165 0.6350936508676438 0.04530400977204452 0.3746126146264712 0.6258599157142364;
 0.5031362585800877 0.8564898411883223 0.658693631618945 0.1629344270814297 0.07056874740042984 0.6424192782063156 0.026511310541621813 0.5857755812734633 0.9402302414249576 0.575474177875879
	)");

  Matrix<type> C = Matrix<type>(R"(
	0.3881699262065219 0.6432882184423532 0.45825289049151663 0.5456167893159349 0.9414648087765252 0.38610263780077425 0.9611905638239142 0.9053506419560637 0.19579113478929644 0.06936130087516545;
 0.10077800137742665 0.018221825651549728 0.0944429607559284 0.6830067734163568 0.07118864846022899 0.3189756302937613 0.8448753109694546 0.023271935735825866 0.8144684825889358 0.28185477477339993;
 0.11816482762165625 0.6967371653641506 0.628942846779884 0.877472013527053 0.7350710438038858 0.8034809303848486 0.2820345725713065 0.17743954377972282 0.7506147516408583 0.806834739267264;
 0.9905051420006733 0.4126176769114265 0.37201808579278317 0.7764129607419968 0.34080354025301784 0.9307573256035647 0.8584127518430118 0.42899402737501835 0.7508710677914974 0.7545428740846823;
 0.10312386883593261 0.9025529066795667 0.5052523724478571 0.8264574661077416 0.32004960103061175 0.8955232284962005 0.3892016787341631 0.01083765148029836 0.9053819764192637 0.09128667678613356;
 0.31931363759041487 0.9500619670508049 0.9506071469375561 0.5734378881232861 0.6318372121697993 0.44844552197831977 0.29321077169806453 0.32866454536991596 0.6725184560770384 0.75237452943768;
 0.7915790437258485 0.7896181427945539 0.09120610304869037 0.49442030470258147 0.057558760016644284 0.5495288823237355 0.441530501373377 0.8877041827582998 0.3509150125520787 0.11706701642760586;
 0.14299168205283586 0.7615106317174722 0.6182180633162611 0.10112267612279024 0.08410680611499743 0.70096913145912 0.07276300636419353 0.8218600592903562 0.7062422271564962 0.08134878064189976;
 0.08483771408519192 0.9866395785011755 0.3742707957561203 0.3706421470668909 0.8127995672575026 0.9472485773838587 0.9860010638228709 0.7533781852589416 0.37625958553091576 0.08350071669866876;
 0.7771469159274368 0.558404249735805 0.4242220092469763 0.906354385094736 0.11119748230615134 0.49262510429085915 0.011353644767419069 0.46866064199412627 0.05630327568183735 0.11881791626807192
	)");

  Matrix<type> R = Matrix<type>(R"(
	9.536636346662478 11.083410477940767 6.808503231535734 8.749024929024406 8.763588111766383 11.026813557437448 10.23219526818223 6.892497014293869 10.304565168307304 8.75109157609557;
 7.926155399458356 9.799508893960525 6.933516484842009 6.412871574180388 9.528104305862984 10.502752374319627 9.172971610154868 7.497264416881409 6.440678571348842 5.482735054729887;
 12.39233894909112 10.931484201406585 8.346181888583608 7.74569755061753 8.64268294817375 9.967491792566744 13.466304366016137 10.367261107503031 10.371832997384303 7.974301656204003;
 5.756178134720649 9.465357487864132 7.626550999785939 5.547868297732207 9.475646743563154 7.826419745914432 9.084438548280712 7.86706401748807 8.182670752665228 4.818816189775516;
 5.7512093462164335 3.5733636008238023 4.907817157155489 5.50589877254475 6.892014776626372 5.280530899748291 6.558077283678714 5.828098413885303 4.19865832153428 4.903761077337054;
 9.247884688423506 8.747628182498067 3.1388653255379184 4.989509472955228 6.739319807594974 7.74486108422584 10.460356469206513 8.04962205321622 6.859927023384741 5.3871781545101385;
 9.700149388413513 10.547205608980494 11.919889507860937 7.309290771281113 11.100398858367432 10.260635155152507 10.881037794608542 8.365152954549593 11.278630670149834 9.449351171323093;
 9.315007403970784 7.782778889380504 8.619623359597782 10.494184295014648 10.96765647150476 11.454422901970046 11.808559502143146 5.290197829531243 9.666039749077036 9.011520227709502;
 12.350794451811609 9.74612958480064 10.81240988255618 10.010699879643447 8.868847584625101 9.657989073782202 11.869408782895126 8.32607740339348 11.440576963881323 10.191308425110323;
 5.6148008027286895 6.580131876458077 5.539115370422657 6.290904922323579 10.459375002595255 9.696604259632998 11.197931070708577 5.125636439474603 7.625027110577795 5.874744383743139
	)");

  gemm_tn_novector_threaded(alpha, A, B, beta, C);

  ASSERT_TRUE(R.AllClose(C));
}
