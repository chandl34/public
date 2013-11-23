import java.util.*;
import java.io.*;

public class converter {
			
	String tempString;
	int tempID, regionID, systemID, oldID, constellationID;
	double security;
	Scanner scanner;
	FileWriter writer;
	
	// moons.txt to MOONSTOKEEP.txt
	public void moonsToKeep() throws Exception{
		scanner.nextLine();
		while(scanner.hasNextLine()){			
			tempString = scanner.nextLine();
			if(tempString.contains("-0."))
				security = Double.parseDouble(tempString.substring(tempString.indexOf('.') -2, tempString.indexOf('.') +3));			
			else if(tempString.contains("."))
				security = Double.parseDouble(tempString.substring(tempString.indexOf('.') -1, tempString.indexOf('.') +3));	
			else if(tempString.contains(",-1,"))
				security = -1;
			else
				security = 1;
			if(security < 0.35)
				writer.write(tempString + "\n");			
		}
		writer.close();
	}	
	
	// MOONSTOKEEP.txt to SYSTEMSTOKEEPalg.txt
	private void systemsToKeepAlg() throws Exception{		
		int i = 1;
		writer.write("if(");
		tempString = scanner.nextLine();
		systemID = Integer.parseInt(tempString.substring(14, 22));	
		oldID = systemID;
		writer.write("(tempID == " + systemID + ")");
		while(scanner.hasNextLine()){	
			tempString = scanner.nextLine();
			systemID = Integer.parseInt(tempString.substring(14, 22));			
			if(i % 3000 == 0){
				writer.write(")writer.write(tempString + \"\\n\"); else if(");
				oldID = systemID;
				writer.write("(tempID == " + systemID + ")");
			}
			i++;
			if(systemID != oldID){
				oldID = systemID;
				writer.write(" || (tempID == " + systemID + ")");
			}
		}
		writer.write(")writer.write(tempString + \"\\n\")");
		writer.close();
	}

	// constellationsConstructor.txt to constellationsConstructor2.txt
	private void constellationsToKeep() throws Exception{		
		writer.write(scanner.nextLine() + "\n");
		while(scanner.hasNextLine()){
			tempString = scanner.nextLine();
			tempID = Integer.parseInt(tempString.substring(0, 8));
			if((tempID != 20000004) && (tempID != 20000005) && (tempID != 20000006) && (tempID != 20000008) && (tempID != 20000009) && (tempID != 20000011) && (tempID != 20000012) && (tempID != 20000015) && (tempID != 20000017) && (tempID != 20000018) && (tempID != 20000019) && (tempID != 20000020) && (tempID != 20000021) && (tempID != 20000022) && (tempID != 20000024) && (tempID != 20000025) && (tempID != 20000026) && (tempID != 20000027) && (tempID != 20000057) && (tempID != 20000059) && (tempID != 20000061) && (tempID != 20000062) && (tempID != 20000198) && (tempID != 20000199) && (tempID != 20000200) && (tempID != 20000201) && (tempID != 20000202) && (tempID != 20000203) && (tempID != 20000204) && (tempID != 20000205) && (tempID != 20000206) && (tempID != 20000207) && (tempID != 20000209) && (tempID != 20000210) && (tempID != 20000243) && (tempID != 20000244) && (tempID != 20000245) && (tempID != 20000247) && (tempID != 20000248) && (tempID != 20000250) && (tempID != 20000251) && (tempID != 20000252) && (tempID != 20000253) && (tempID != 20000255) && (tempID != 20000256) && (tempID != 20000257) && (tempID != 20000302) && (tempID != 20000303) && (tempID != 20000305) && (tempID != 20000307) && (tempID != 20000322) && (tempID != 20000323) && (tempID != 20000324) && (tempID != 20000325) && (tempID != 20000326) && (tempID != 20000327) && (tempID != 20000329) && (tempID != 20000331) && (tempID != 20000332) && (tempID != 20000334) && (tempID != 20000350) && (tempID != 20000367) && (tempID != 20000369) && (tempID != 20000370) && (tempID != 20000371) && (tempID != 20000373) && (tempID != 20000376) && (tempID != 20000377) && (tempID != 20000386) && (tempID != 20000387) && (tempID != 20000388) && (tempID != 20000389) && (tempID != 20000390) && (tempID != 20000391) && (tempID != 20000392) && (tempID != 20000393) && (tempID != 20000394) && (tempID != 20000395) && (tempID != 20000396) && (tempID != 20000397) && (tempID != 20000400) && (tempID != 20000401) && (tempID != 20000402) && (tempID != 20000403) && (tempID != 20000405) && (tempID != 20000406) && (tempID != 20000407) && (tempID != 20000408) && (tempID != 20000409) && (tempID != 20000410) && (tempID != 20000411) && (tempID != 20000413) && (tempID != 20000434) && (tempID != 20000435) && (tempID != 20000438) && (tempID != 20000439) && (tempID != 20000440) && (tempID != 20000441) && (tempID != 20000442) && (tempID != 20000443) && (tempID != 20000444) && (tempID != 20000446) && (tempID != 20000448) && (tempID != 20000449) && (tempID != 20000450) && (tempID != 20000452) && (tempID != 20000492) && (tempID != 20000493) && (tempID != 20000494) && (tempID != 20000495) && (tempID != 20000496) && (tempID != 20000497) && (tempID != 20000498) && (tempID != 20000499) && (tempID != 20000500) && (tempID != 20000501) && (tempID != 20000503) && (tempID != 20000504) && (tempID != 20000509) && (tempID != 20000510) && (tempID != 20000511) && (tempID != 20000512) && (tempID != 20000513) && (tempID != 20000514) && (tempID != 20000515) && (tempID != 20000516) && (tempID != 20000517) && (tempID != 20000521) && (tempID != 20000523) && (tempID != 20000557) && (tempID != 20000564) && (tempID != 20000565) && (tempID != 20000566) && (tempID != 20000568) && (tempID != 20000570) && (tempID != 20000571) && (tempID != 20000596) && (tempID != 20000597) && (tempID != 20000598) && (tempID != 20000599) && (tempID != 20000601) && (tempID != 20000602) && (tempID != 20000603) && (tempID != 20000604) && (tempID != 20000606) && (tempID != 20000607) && (tempID != 20000608) && (tempID != 20000622) && (tempID != 20000727) && (tempID != 20000728) && (tempID != 20000735) && (tempID != 20000737) && (tempID != 20000738) && (tempID != 20000739) && (tempID != 20000740) && (tempID != 20000743) && (tempID != 20000760) && (tempID != 20000761) && (tempID != 20000762) && (tempID != 20000763) && (tempID != 20000764) && (tempID != 20000767) && (tempID != 20000768) && (tempID != 20000774) && (tempID != 20000776) && (tempID != 20000777) && (tempID != 20000779) && (tempID != 20000780))
					writer.write(tempString + "\n");
		}
		writer.close();
	}
	
	// systems.txt to SYSTEMSTOKEEP.txt
	private void systemsToKeep() throws Exception{
		scanner.nextLine();
		while(scanner.hasNextLine()){			
			tempString = scanner.nextLine();
			tempID = Integer.parseInt(tempString.substring(0, 8));
			if((tempID == 30000012) || (tempID == 30000015) || (tempID == 30000017) || (tempID == 30000018) || (tempID == 

				30000019) || (tempID == 30000020) || (tempID == 30000021) || (tempID == 30000022) || (tempID == 30000044) || 

				(tempID == 30000045) || (tempID == 30000046) || (tempID == 30000049) || (tempID == 30000075) || (tempID == 

				30000089) || (tempID == 30000090) || (tempID == 30000091) || (tempID == 30000092) || (tempID == 30000094) || 

				(tempID == 30000095) || (tempID == 30000096) || (tempID == 30000097) || (tempID == 30000100) || (tempID == 

				30000102) || (tempID == 30000104) || (tempID == 30000114) || (tempID == 30000115) || (tempID == 30000116) || 

				(tempID == 30000117) || (tempID == 30000163) || (tempID == 30000164) || (tempID == 30000195) || (tempID == 

				30000196) || (tempID == 30000197) || (tempID == 30000198) || (tempID == 30000199) || (tempID == 30000200) || 

				(tempID == 30000205) || (tempID == 30000207) || (tempID == 30000208) || (tempID == 30000209) || (tempID == 

				30000210) || (tempID == 30000211) || (tempID == 30000212) || (tempID == 30000213) || (tempID == 30000214) || 

				(tempID == 30000215) || (tempID == 30000216) || (tempID == 30000217) || (tempID == 30000218) || (tempID == 

				30000219) || (tempID == 30000220) || (tempID == 30000221) || (tempID == 30000222) || (tempID == 30000223) || 

				(tempID == 30000224) || (tempID == 30000225) || (tempID == 30000226) || (tempID == 30000227) || (tempID == 

				30000228) || (tempID == 30000229) || (tempID == 30000230) || (tempID == 30000231) || (tempID == 

				30000232))writer.write(tempString + "\n"); else if((tempID == 30000232) || (tempID == 30000233) || (tempID == 

				30000234) || (tempID == 30000235) || (tempID == 30000236) || (tempID == 30000237) || (tempID == 30000238) || 

				(tempID == 30000239) || (tempID == 30000240) || (tempID == 30000241) || (tempID == 30000242) || (tempID == 

				30000243) || (tempID == 30000244) || (tempID == 30000245) || (tempID == 30000246) || (tempID == 30000247) || 

				(tempID == 30000248) || (tempID == 30000249) || (tempID == 30000250) || (tempID == 30000251) || (tempID == 

				30000252) || (tempID == 30000253) || (tempID == 30000254) || (tempID == 30000255) || (tempID == 30000256) || 

				(tempID == 30000257) || (tempID == 30000258) || (tempID == 30000259) || (tempID == 30000260) || (tempID == 

				30000261) || (tempID == 30000262) || (tempID == 30000263) || (tempID == 30000264) || (tempID == 30000265) || 

				(tempID == 30000266) || (tempID == 30000267) || (tempID == 30000268) || (tempID == 30000269) || (tempID == 

				30000270) || (tempID == 30000271) || (tempID == 30000272) || (tempID == 30000273) || (tempID == 30000274) || 

				(tempID == 30000275) || (tempID == 30000276) || (tempID == 30000277) || (tempID == 30000278) || (tempID == 

				30000279) || (tempID == 30000280) || (tempID == 30000281) || (tempID == 30000282) || (tempID == 30000283) || 

				(tempID == 30000284) || (tempID == 30000285) || (tempID == 30000286) || (tempID == 30000287) || (tempID == 

				30000288) || (tempID == 30000289) || (tempID == 30000290) || (tempID == 30000291) || (tempID == 30000292) || 

				(tempID == 30000293) || (tempID == 30000294) || (tempID == 30000295) || (tempID == 30000296) || (tempID == 

				30000297) || (tempID == 30000298) || (tempID == 30000299) || (tempID == 30000300) || (tempID == 30000301) || 

				(tempID == 30000302) || (tempID == 30000303) || (tempID == 30000304) || (tempID == 30000305) || (tempID == 

				30000306))writer.write(tempString + "\n"); else if((tempID == 30000306) || (tempID == 30000307) || (tempID == 

				30000308) || (tempID == 30000309) || (tempID == 30000310) || (tempID == 30000311) || (tempID == 30000312) || 

				(tempID == 30000313) || (tempID == 30000314) || (tempID == 30000315) || (tempID == 30000316) || (tempID == 

				30000317) || (tempID == 30000318) || (tempID == 30000319) || (tempID == 30000320) || (tempID == 30000321) || 

				(tempID == 30000322) || (tempID == 30000323) || (tempID == 30000324) || (tempID == 30000325) || (tempID == 

				30000326) || (tempID == 30000327) || (tempID == 30000328) || (tempID == 30000329) || (tempID == 30000330) || 

				(tempID == 30000331) || (tempID == 30000332) || (tempID == 30000333) || (tempID == 30000334) || (tempID == 

				30000335) || (tempID == 30000336) || (tempID == 30000337) || (tempID == 30000338) || (tempID == 30000339) || 

				(tempID == 30000340) || (tempID == 30000341) || (tempID == 30000342) || (tempID == 30000343) || (tempID == 

				30000344) || (tempID == 30000345) || (tempID == 30000346) || (tempID == 30000347) || (tempID == 30000348) || 

				(tempID == 30000349) || (tempID == 30000350) || (tempID == 30000351) || (tempID == 30000352) || (tempID == 

				30000353) || (tempID == 30000354) || (tempID == 30000355) || (tempID == 30000356) || (tempID == 30000357) || 

				(tempID == 30000358) || (tempID == 30000359) || (tempID == 30000360) || (tempID == 30000361) || (tempID == 

				30000362) || (tempID == 30000363) || (tempID == 30000364) || (tempID == 30000365) || (tempID == 30000366) || 

				(tempID == 30000367) || (tempID == 30000368) || (tempID == 30000369) || (tempID == 30000370) || (tempID == 

				30000371) || (tempID == 30000372) || (tempID == 30000373) || (tempID == 30000374) || (tempID == 30000375) || 

				(tempID == 30000376) || (tempID == 30000378))writer.write(tempString + "\n"); else if((tempID == 30000378) || 

				(tempID == 30000379) || (tempID == 30000380) || (tempID == 30000381) || (tempID == 30000382) || (tempID == 

				30000383) || (tempID == 30000384) || (tempID == 30000385) || (tempID == 30000386) || (tempID == 30000388) || 

				(tempID == 30000389) || (tempID == 30000390) || (tempID == 30000391) || (tempID == 30000392) || (tempID == 

				30000393) || (tempID == 30000394) || (tempID == 30000407) || (tempID == 30000414) || (tempID == 30000415) || 

				(tempID == 30000416) || (tempID == 30000417) || (tempID == 30000418) || (tempID == 30000419) || (tempID == 

				30000433) || (tempID == 30000434) || (tempID == 30000435) || (tempID == 30000436) || (tempID == 30000437) || 

				(tempID == 30000438) || (tempID == 30000439) || (tempID == 30000440) || (tempID == 30000441) || (tempID == 

				30000442) || (tempID == 30000443) || (tempID == 30000444) || (tempID == 30000445) || (tempID == 30000446) || 

				(tempID == 30000447) || (tempID == 30000448) || (tempID == 30000449) || (tempID == 30000450) || (tempID == 

				30000451) || (tempID == 30000452) || (tempID == 30000453) || (tempID == 30000454) || (tempID == 30000455) || 

				(tempID == 30000456) || (tempID == 30000457) || (tempID == 30000458) || (tempID == 30000459) || (tempID == 

				30000460) || (tempID == 30000461) || (tempID == 30000462) || (tempID == 30000463) || (tempID == 30000464) || 

				(tempID == 30000465) || (tempID == 30000466) || (tempID == 30000467) || (tempID == 30000468) || (tempID == 

				30000469) || (tempID == 30000470) || (tempID == 30000471) || (tempID == 30000472) || (tempID == 30000473) || 

				(tempID == 30000474) || (tempID == 30000475) || (tempID == 30000476) || (tempID == 30000477) || (tempID == 

				30000478) || (tempID == 30000479) || (tempID == 30000480) || (tempID == 30000481) || (tempID == 30000482) || 

				(tempID == 30000483) || (tempID == 30000484))writer.write(tempString + "\n"); else if((tempID == 30000484) || 

				(tempID == 30000485) || (tempID == 30000486) || (tempID == 30000487) || (tempID == 30000488) || (tempID == 

				30000489) || (tempID == 30000490) || (tempID == 30000491) || (tempID == 30000492) || (tempID == 30000493) || 

				(tempID == 30000494) || (tempID == 30000495) || (tempID == 30000496) || (tempID == 30000497) || (tempID == 

				30000498) || (tempID == 30000499) || (tempID == 30000500) || (tempID == 30000501) || (tempID == 30000502) || 

				(tempID == 30000503) || (tempID == 30000504) || (tempID == 30000505) || (tempID == 30000506) || (tempID == 

				30000507) || (tempID == 30000508) || (tempID == 30000509) || (tempID == 30000510) || (tempID == 30000511) || 

				(tempID == 30000512) || (tempID == 30000513) || (tempID == 30000514) || (tempID == 30000515) || (tempID == 

				30000516) || (tempID == 30000517) || (tempID == 30000518) || (tempID == 30000519) || (tempID == 30000520) || 

				(tempID == 30000521) || (tempID == 30000522) || (tempID == 30000523) || (tempID == 30000524) || (tempID == 

				30000525) || (tempID == 30000526) || (tempID == 30000527) || (tempID == 30000528) || (tempID == 30000529) || 

				(tempID == 30000530) || (tempID == 30000531) || (tempID == 30000532) || (tempID == 30000533) || (tempID == 

				30000534) || (tempID == 30000535) || (tempID == 30000536) || (tempID == 30000537) || (tempID == 30000538) || 

				(tempID == 30000539) || (tempID == 30000540) || (tempID == 30000541) || (tempID == 30000542) || (tempID == 

				30000543) || (tempID == 30000544) || (tempID == 30000545) || (tempID == 30000546) || (tempID == 30000547) || 

				(tempID == 30000548) || (tempID == 30000549) || (tempID == 30000550))writer.write(tempString + "\n"); else 

				if((tempID == 30000550) || (tempID == 30000551) || (tempID == 30000552) || (tempID == 30000553) || (tempID == 

				30000554) || (tempID == 30000555) || (tempID == 30000556) || (tempID == 30000557) || (tempID == 30000558) || 

				(tempID == 30000559) || (tempID == 30000560) || (tempID == 30000561) || (tempID == 30000562) || (tempID == 

				30000563) || (tempID == 30000564) || (tempID == 30000565) || (tempID == 30000566) || (tempID == 30000567) || 

				(tempID == 30000568) || (tempID == 30000569) || (tempID == 30000570) || (tempID == 30000571) || (tempID == 

				30000572) || (tempID == 30000573) || (tempID == 30000574) || (tempID == 30000575) || (tempID == 30000576) || 

				(tempID == 30000577) || (tempID == 30000578) || (tempID == 30000579) || (tempID == 30000580) || (tempID == 

				30000581) || (tempID == 30000582) || (tempID == 30000583) || (tempID == 30000584) || (tempID == 30000585) || 

				(tempID == 30000586) || (tempID == 30000587) || (tempID == 30000588) || (tempID == 30000589) || (tempID == 

				30000590) || (tempID == 30000591) || (tempID == 30000592) || (tempID == 30000593) || (tempID == 30000594) || 

				(tempID == 30000595) || (tempID == 30000596) || (tempID == 30000597) || (tempID == 30000598) || (tempID == 

				30000599) || (tempID == 30000600) || (tempID == 30000601) || (tempID == 30000602) || (tempID == 30000603) || 

				(tempID == 30000604) || (tempID == 30000605) || (tempID == 30000606) || (tempID == 30000607) || (tempID == 

				30000608) || (tempID == 30000609) || (tempID == 30000610) || (tempID == 30000611) || (tempID == 30000612) || 

				(tempID == 30000613) || (tempID == 30000614) || (tempID == 30000615) || (tempID == 30000616) || (tempID == 

				30000617) || (tempID == 30000618) || (tempID == 30000619))writer.write(tempString + "\n"); else if((tempID == 

				30000619) || (tempID == 30000620) || (tempID == 30000621) || (tempID == 30000622) || (tempID == 30000623) || 

				(tempID == 30000624) || (tempID == 30000625) || (tempID == 30000626) || (tempID == 30000627) || (tempID == 

				30000628) || (tempID == 30000629) || (tempID == 30000630) || (tempID == 30000631) || (tempID == 30000632) || 

				(tempID == 30000633) || (tempID == 30000634) || (tempID == 30000635) || (tempID == 30000636) || (tempID == 

				30000637) || (tempID == 30000638) || (tempID == 30000639) || (tempID == 30000640) || (tempID == 30000641) || 

				(tempID == 30000642) || (tempID == 30000643) || (tempID == 30000644) || (tempID == 30000645) || (tempID == 

				30000646) || (tempID == 30000647) || (tempID == 30000648) || (tempID == 30000649) || (tempID == 30000650) || 

				(tempID == 30000651) || (tempID == 30000652) || (tempID == 30000653) || (tempID == 30000654) || (tempID == 

				30000655) || (tempID == 30000656) || (tempID == 30000657) || (tempID == 30000658) || (tempID == 30000659) || 

				(tempID == 30000660) || (tempID == 30000661) || (tempID == 30000662) || (tempID == 30000663) || (tempID == 

				30000664) || (tempID == 30000665) || (tempID == 30000666) || (tempID == 30000667) || (tempID == 30000668) || 

				(tempID == 30000669) || (tempID == 30000670) || (tempID == 30000671) || (tempID == 30000672) || (tempID == 

				30000673) || (tempID == 30000674) || (tempID == 30000675) || (tempID == 30000676) || (tempID == 30000677) || 

				(tempID == 30000678) || (tempID == 30000679) || (tempID == 30000680) || (tempID == 30000681) || (tempID == 

				30000682) || (tempID == 30000683))writer.write(tempString + "\n"); else if((tempID == 30000683) || (tempID == 

				30000684) || (tempID == 30000685) || (tempID == 30000686) || (tempID == 30000687) || (tempID == 30000688) || 

				(tempID == 30000689) || (tempID == 30000690) || (tempID == 30000691) || (tempID == 30000692) || (tempID == 

				30000693) || (tempID == 30000694) || (tempID == 30000695) || (tempID == 30000696) || (tempID == 30000697) || 

				(tempID == 30000698) || (tempID == 30000699) || (tempID == 30000700) || (tempID == 30000701) || (tempID == 

				30000702) || (tempID == 30000703) || (tempID == 30000704) || (tempID == 30000705) || (tempID == 30000706) || 

				(tempID == 30000707) || (tempID == 30000708) || (tempID == 30000709) || (tempID == 30000710) || (tempID == 

				30000711) || (tempID == 30000712) || (tempID == 30000713) || (tempID == 30000714) || (tempID == 30000715) || 

				(tempID == 30000716) || (tempID == 30000717) || (tempID == 30000718) || (tempID == 30000719) || (tempID == 

				30000720) || (tempID == 30000721) || (tempID == 30000722) || (tempID == 30000723) || (tempID == 30000724) || 

				(tempID == 30000725) || (tempID == 30000726) || (tempID == 30000727) || (tempID == 30000728) || (tempID == 

				30000729) || (tempID == 30000730) || (tempID == 30000731) || (tempID == 30000732) || (tempID == 30000733) || 

				(tempID == 30000734) || (tempID == 30000735) || (tempID == 30000736) || (tempID == 30000737) || (tempID == 

				30000738) || (tempID == 30000739) || (tempID == 30000740) || (tempID == 30000741) || (tempID == 30000742) || 

				(tempID == 30000743) || (tempID == 30000744) || (tempID == 30000745) || (tempID == 30000746) || (tempID == 

				30000747) || (tempID == 30000748) || (tempID == 30000749) || (tempID == 30000750) || (tempID == 30000751) || 

				(tempID == 30000752) || (tempID == 30000753) || (tempID == 30000754) || (tempID == 30000755) || (tempID == 

				30000756))writer.write(tempString + "\n"); else if((tempID == 30000756) || (tempID == 30000757) || (tempID == 

				30000758) || (tempID == 30000759) || (tempID == 30000760) || (tempID == 30000761) || (tempID == 30000762) || 

				(tempID == 30000763) || (tempID == 30000764) || (tempID == 30000765) || (tempID == 30000766) || (tempID == 

				30000767) || (tempID == 30000768) || (tempID == 30000769) || (tempID == 30000770) || (tempID == 30000771) || 

				(tempID == 30000772) || (tempID == 30000773) || (tempID == 30000774) || (tempID == 30000775) || (tempID == 

				30000776) || (tempID == 30000777) || (tempID == 30000778) || (tempID == 30000779) || (tempID == 30000780) || 

				(tempID == 30000781) || (tempID == 30000782) || (tempID == 30000783) || (tempID == 30000784) || (tempID == 

				30000785) || (tempID == 30000786) || (tempID == 30000787) || (tempID == 30000788) || (tempID == 30000789) || 

				(tempID == 30000790) || (tempID == 30000791) || (tempID == 30000792) || (tempID == 30000793) || (tempID == 

				30000794) || (tempID == 30000795) || (tempID == 30000796) || (tempID == 30000797) || (tempID == 30000798) || 

				(tempID == 30000799) || (tempID == 30000800) || (tempID == 30000801) || (tempID == 30000802) || (tempID == 

				30000803) || (tempID == 30000804) || (tempID == 30000805) || (tempID == 30000806) || (tempID == 30000807) || 

				(tempID == 30000808) || (tempID == 30000809) || (tempID == 30000810) || (tempID == 30000811) || (tempID == 

				30000812) || (tempID == 30000813) || (tempID == 30000814) || (tempID == 30000815) || (tempID == 30000816) || 

				(tempID == 30000817) || (tempID == 30000818) || (tempID == 30000819))writer.write(tempString + "\n"); else 

				if((tempID == 30000819) || (tempID == 30000820) || (tempID == 30000821) || (tempID == 30000822) || (tempID == 

				30000823) || (tempID == 30000824) || (tempID == 30000825) || (tempID == 30000826) || (tempID == 30000827) || 

				(tempID == 30000828) || (tempID == 30000829) || (tempID == 30000830) || (tempID == 30000831) || (tempID == 

				30000832) || (tempID == 30000833) || (tempID == 30000834) || (tempID == 30000835) || (tempID == 30000836) || 

				(tempID == 30000837) || (tempID == 30000838) || (tempID == 30000839) || (tempID == 30000840) || (tempID == 

				30000841) || (tempID == 30000842) || (tempID == 30000843) || (tempID == 30000844) || (tempID == 30000845) || 

				(tempID == 30000846) || (tempID == 30000847) || (tempID == 30000848) || (tempID == 30000849) || (tempID == 

				30000850) || (tempID == 30000851) || (tempID == 30000852) || (tempID == 30000853) || (tempID == 30000854) || 

				(tempID == 30000855) || (tempID == 30000856) || (tempID == 30000857) || (tempID == 30000858) || (tempID == 

				30000859) || (tempID == 30000860) || (tempID == 30000861) || (tempID == 30000862) || (tempID == 30000863) || 

				(tempID == 30000864) || (tempID == 30000865) || (tempID == 30000866) || (tempID == 30000867) || (tempID == 

				30000868) || (tempID == 30000869) || (tempID == 30000870) || (tempID == 30000871) || (tempID == 30000872) || 

				(tempID == 30000873) || (tempID == 30000874) || (tempID == 30000875) || (tempID == 30000876) || (tempID == 

				30000877) || (tempID == 30000878) || (tempID == 30000879) || (tempID == 30000880))writer.write(tempString + 

				"\n"); else if((tempID == 30000880) || (tempID == 30000881) || (tempID == 30000882) || (tempID == 30000883) || 

				(tempID == 30000884) || (tempID == 30000885) || (tempID == 30000886) || (tempID == 30000887) || (tempID == 

				30000888) || (tempID == 30000889) || (tempID == 30000890) || (tempID == 30000891) || (tempID == 30000892) || 

				(tempID == 30000893) || (tempID == 30000894) || (tempID == 30000895) || (tempID == 30000896) || (tempID == 

				30000897) || (tempID == 30000898) || (tempID == 30000899) || (tempID == 30000900) || (tempID == 30000901) || 

				(tempID == 30000902) || (tempID == 30000903) || (tempID == 30000904) || (tempID == 30000905) || (tempID == 

				30000906) || (tempID == 30000907) || (tempID == 30000908) || (tempID == 30000909) || (tempID == 30000910) || 

				(tempID == 30000911) || (tempID == 30000912) || (tempID == 30000913) || (tempID == 30000914) || (tempID == 

				30000915) || (tempID == 30000916) || (tempID == 30000917) || (tempID == 30000918) || (tempID == 30000919) || 

				(tempID == 30000920) || (tempID == 30000921) || (tempID == 30000922) || (tempID == 30000923) || (tempID == 

				30000924) || (tempID == 30000925) || (tempID == 30000926) || (tempID == 30000927) || (tempID == 30000928) || 

				(tempID == 30000929) || (tempID == 30000930) || (tempID == 30000931) || (tempID == 30000932) || (tempID == 

				30000933) || (tempID == 30000934) || (tempID == 30000935) || (tempID == 30000936) || (tempID == 30000937) || 

				(tempID == 30000938) || (tempID == 30000939) || (tempID == 30000940) || (tempID == 30000941) || (tempID == 

				30000942) || (tempID == 30000943) || (tempID == 30000944) || (tempID == 30000945) || (tempID == 30000946) || 

				(tempID == 30000947) || (tempID == 30000948) || (tempID == 30000949))writer.write(tempString + "\n"); else 

				if((tempID == 30000949) || (tempID == 30000950) || (tempID == 30000951) || (tempID == 30000952) || (tempID == 

				30000953) || (tempID == 30000954) || (tempID == 30000955) || (tempID == 30000956) || (tempID == 30000957) || 

				(tempID == 30000958) || (tempID == 30000959) || (tempID == 30000960) || (tempID == 30000961) || (tempID == 

				30000962) || (tempID == 30000963) || (tempID == 30000964) || (tempID == 30000965) || (tempID == 30000966) || 

				(tempID == 30000967) || (tempID == 30000968) || (tempID == 30000969) || (tempID == 30000970) || (tempID == 

				30000971) || (tempID == 30000972) || (tempID == 30000973) || (tempID == 30000974) || (tempID == 30000975) || 

				(tempID == 30000976) || (tempID == 30000977) || (tempID == 30000978) || (tempID == 30000979) || (tempID == 

				30000980) || (tempID == 30000981) || (tempID == 30000982) || (tempID == 30000983) || (tempID == 30000984) || 

				(tempID == 30000985) || (tempID == 30000986) || (tempID == 30000987) || (tempID == 30000988) || (tempID == 

				30000989) || (tempID == 30000990) || (tempID == 30000991) || (tempID == 30000992) || (tempID == 30000993) || 

				(tempID == 30000994) || (tempID == 30000995) || (tempID == 30000996) || (tempID == 30000997) || (tempID == 

				30000998) || (tempID == 30000999) || (tempID == 30001000) || (tempID == 30001001) || (tempID == 30001002) || 

				(tempID == 30001003) || (tempID == 30001004) || (tempID == 30001005) || (tempID == 30001006) || (tempID == 

				30001007) || (tempID == 30001008) || (tempID == 30001009) || (tempID == 30001010) || (tempID == 30001011) || 

				(tempID == 30001012) || (tempID == 30001013) || (tempID == 30001014) || (tempID == 30001015) || (tempID == 

				30001016) || (tempID == 30001017) || (tempID == 30001018))writer.write(tempString + "\n"); else if((tempID == 

				30001018) || (tempID == 30001019) || (tempID == 30001020) || (tempID == 30001021) || (tempID == 30001022) || 

				(tempID == 30001023) || (tempID == 30001024) || (tempID == 30001025) || (tempID == 30001026) || (tempID == 

				30001027) || (tempID == 30001028) || (tempID == 30001029) || (tempID == 30001030) || (tempID == 30001031) || 

				(tempID == 30001032) || (tempID == 30001033) || (tempID == 30001034) || (tempID == 30001035) || (tempID == 

				30001036) || (tempID == 30001037) || (tempID == 30001038) || (tempID == 30001039) || (tempID == 30001040) || 

				(tempID == 30001041) || (tempID == 30001042) || (tempID == 30001043) || (tempID == 30001044) || (tempID == 

				30001045) || (tempID == 30001046) || (tempID == 30001047) || (tempID == 30001048) || (tempID == 30001049) || 

				(tempID == 30001050) || (tempID == 30001051) || (tempID == 30001052) || (tempID == 30001053) || (tempID == 

				30001054) || (tempID == 30001055) || (tempID == 30001056) || (tempID == 30001057) || (tempID == 30001058) || 

				(tempID == 30001059) || (tempID == 30001060) || (tempID == 30001061) || (tempID == 30001062) || (tempID == 

				30001063) || (tempID == 30001064) || (tempID == 30001065) || (tempID == 30001066) || (tempID == 30001067) || 

				(tempID == 30001068) || (tempID == 30001069) || (tempID == 30001070) || (tempID == 30001071) || (tempID == 

				30001072) || (tempID == 30001073) || (tempID == 30001074) || (tempID == 30001075) || (tempID == 30001076) || 

				(tempID == 30001077) || (tempID == 30001078) || (tempID == 30001079) || (tempID == 30001080) || (tempID == 

				30001081) || (tempID == 30001082) || (tempID == 30001083))writer.write(tempString + "\n"); else if((tempID == 

				30001083) || (tempID == 30001084) || (tempID == 30001085) || (tempID == 30001086) || (tempID == 30001087) || 

				(tempID == 30001088) || (tempID == 30001089) || (tempID == 30001090) || (tempID == 30001091) || (tempID == 

				30001092) || (tempID == 30001093) || (tempID == 30001094) || (tempID == 30001095) || (tempID == 30001096) || 

				(tempID == 30001097) || (tempID == 30001098) || (tempID == 30001099) || (tempID == 30001100) || (tempID == 

				30001101) || (tempID == 30001102) || (tempID == 30001103) || (tempID == 30001104) || (tempID == 30001105) || 

				(tempID == 30001106) || (tempID == 30001107) || (tempID == 30001108) || (tempID == 30001109) || (tempID == 

				30001110) || (tempID == 30001111) || (tempID == 30001112) || (tempID == 30001113) || (tempID == 30001114) || 

				(tempID == 30001115) || (tempID == 30001116) || (tempID == 30001117) || (tempID == 30001118) || (tempID == 

				30001119) || (tempID == 30001120) || (tempID == 30001121) || (tempID == 30001122) || (tempID == 30001123) || 

				(tempID == 30001124) || (tempID == 30001125) || (tempID == 30001126) || (tempID == 30001127) || (tempID == 

				30001128) || (tempID == 30001129) || (tempID == 30001130) || (tempID == 30001131) || (tempID == 30001132) || 

				(tempID == 30001133) || (tempID == 30001134) || (tempID == 30001135) || (tempID == 30001136) || (tempID == 

				30001137) || (tempID == 30001138) || (tempID == 30001139) || (tempID == 30001140) || (tempID == 30001141) || 

				(tempID == 30001142) || (tempID == 30001143) || (tempID == 30001144) || (tempID == 30001145) || (tempID == 

				30001146) || (tempID == 30001147) || (tempID == 30001148) || (tempID == 30001149) || (tempID == 30001150) || 

				(tempID == 30001151) || (tempID == 30001152) || (tempID == 30001153) || (tempID == 30001154) || (tempID == 

				30001155))writer.write(tempString + "\n"); else if((tempID == 30001155) || (tempID == 30001156) || (tempID == 

				30001157) || (tempID == 30001158) || (tempID == 30001159) || (tempID == 30001160) || (tempID == 30001161) || 

				(tempID == 30001162) || (tempID == 30001163) || (tempID == 30001164) || (tempID == 30001165) || (tempID == 

				30001166) || (tempID == 30001167) || (tempID == 30001168) || (tempID == 30001169) || (tempID == 30001170) || 

				(tempID == 30001171) || (tempID == 30001172) || (tempID == 30001173) || (tempID == 30001174) || (tempID == 

				30001175) || (tempID == 30001176) || (tempID == 30001177) || (tempID == 30001178) || (tempID == 30001179) || 

				(tempID == 30001180) || (tempID == 30001181) || (tempID == 30001182) || (tempID == 30001183) || (tempID == 

				30001184) || (tempID == 30001185) || (tempID == 30001186) || (tempID == 30001187) || (tempID == 30001188) || 

				(tempID == 30001189) || (tempID == 30001190) || (tempID == 30001191) || (tempID == 30001192) || (tempID == 

				30001193) || (tempID == 30001194) || (tempID == 30001195) || (tempID == 30001196) || (tempID == 30001197) || 

				(tempID == 30001198) || (tempID == 30001199) || (tempID == 30001200) || (tempID == 30001201) || (tempID == 

				30001202) || (tempID == 30001203) || (tempID == 30001204) || (tempID == 30001205) || (tempID == 30001206) || 

				(tempID == 30001207) || (tempID == 30001208) || (tempID == 30001209) || (tempID == 30001210) || (tempID == 

				30001211) || (tempID == 30001212) || (tempID == 30001213) || (tempID == 30001214) || (tempID == 30001215) || 

				(tempID == 30001216) || (tempID == 30001217) || (tempID == 30001218) || (tempID == 30001219) || (tempID == 

				30001220) || (tempID == 30001221) || (tempID == 30001222) || (tempID == 30001223) || (tempID == 30001224) || 

				(tempID == 30001225) || (tempID == 30001226) || (tempID == 30001227) || (tempID == 30001228) || (tempID == 

				30001229))writer.write(tempString + "\n"); else if((tempID == 30001229) || (tempID == 30001230) || (tempID == 

				30001231) || (tempID == 30001232) || (tempID == 30001233) || (tempID == 30001234) || (tempID == 30001235) || 

				(tempID == 30001236) || (tempID == 30001237) || (tempID == 30001238) || (tempID == 30001239) || (tempID == 

				30001240) || (tempID == 30001241) || (tempID == 30001242) || (tempID == 30001243) || (tempID == 30001244) || 

				(tempID == 30001245) || (tempID == 30001246) || (tempID == 30001247) || (tempID == 30001248) || (tempID == 

				30001249) || (tempID == 30001250) || (tempID == 30001251) || (tempID == 30001252) || (tempID == 30001253) || 

				(tempID == 30001254) || (tempID == 30001255) || (tempID == 30001256) || (tempID == 30001257) || (tempID == 

				30001258) || (tempID == 30001259) || (tempID == 30001260) || (tempID == 30001261) || (tempID == 30001262) || 

				(tempID == 30001263) || (tempID == 30001264) || (tempID == 30001265) || (tempID == 30001266) || (tempID == 

				30001267) || (tempID == 30001268) || (tempID == 30001269) || (tempID == 30001270) || (tempID == 30001271) || 

				(tempID == 30001272) || (tempID == 30001273) || (tempID == 30001274) || (tempID == 30001275) || (tempID == 

				30001276) || (tempID == 30001277) || (tempID == 30001278) || (tempID == 30001279) || (tempID == 30001280) || 

				(tempID == 30001281) || (tempID == 30001282) || (tempID == 30001283) || (tempID == 30001284) || (tempID == 

				30001285) || (tempID == 30001286) || (tempID == 30001287) || (tempID == 30001288) || (tempID == 30001289) || 

				(tempID == 30001290) || (tempID == 30001291) || (tempID == 30001292))writer.write(tempString + "\n"); else 

				if((tempID == 30001293) || (tempID == 30001294) || (tempID == 30001295) || (tempID == 30001296) || (tempID == 

				30001297) || (tempID == 30001298) || (tempID == 30001299) || (tempID == 30001300) || (tempID == 30001301) || 

				(tempID == 30001302) || (tempID == 30001303) || (tempID == 30001304) || (tempID == 30001305) || (tempID == 

				30001306) || (tempID == 30001307) || (tempID == 30001308) || (tempID == 30001309) || (tempID == 30001310) || 

				(tempID == 30001311) || (tempID == 30001312) || (tempID == 30001313) || (tempID == 30001314) || (tempID == 

				30001315) || (tempID == 30001316) || (tempID == 30001317) || (tempID == 30001318) || (tempID == 30001319) || 

				(tempID == 30001320) || (tempID == 30001321) || (tempID == 30001322) || (tempID == 30001323) || (tempID == 

				30001324) || (tempID == 30001325) || (tempID == 30001326) || (tempID == 30001327) || (tempID == 30001328) || 

				(tempID == 30001329) || (tempID == 30001330) || (tempID == 30001331) || (tempID == 30001332) || (tempID == 

				30001333) || (tempID == 30001334) || (tempID == 30001335) || (tempID == 30001336) || (tempID == 30001337) || 

				(tempID == 30001338) || (tempID == 30001339) || (tempID == 30001340) || (tempID == 30001341) || (tempID == 

				30001342) || (tempID == 30001343) || (tempID == 30001344) || (tempID == 30001345) || (tempID == 30001346) || 

				(tempID == 30001347) || (tempID == 30001348) || (tempID == 30001349) || (tempID == 30001350) || (tempID == 

				30001351) || (tempID == 30001352) || (tempID == 30001353) || (tempID == 30001354) || (tempID == 30001355) || 

				(tempID == 30001422) || (tempID == 30001437) || (tempID == 30001440) || (tempID == 

				30001441))writer.write(tempString + "\n"); else if((tempID == 30001441) || (tempID == 30001442) || (tempID == 

				30001446) || (tempID == 30001447) || (tempID == 30001448) || (tempID == 30001449) || (tempID == 30001450) || 

				(tempID == 30001451) || (tempID == 30001452) || (tempID == 30001453) || (tempID == 30001454) || (tempID == 

				30001455) || (tempID == 30001456) || (tempID == 30001457) || (tempID == 30001458) || (tempID == 30001459) || 

				(tempID == 30001460) || (tempID == 30001461) || (tempID == 30001462) || (tempID == 30001463) || (tempID == 

				30001464) || (tempID == 30001465) || (tempID == 30001466) || (tempID == 30001467) || (tempID == 30001468) || 

				(tempID == 30001469) || (tempID == 30001470) || (tempID == 30001471) || (tempID == 30001472) || (tempID == 

				30001473) || (tempID == 30001474) || (tempID == 30001475) || (tempID == 30001476) || (tempID == 30001477) || 

				(tempID == 30001478) || (tempID == 30001479) || (tempID == 30001480) || (tempID == 30001481) || (tempID == 

				30001482) || (tempID == 30001483) || (tempID == 30001484) || (tempID == 30001485) || (tempID == 30001486) || 

				(tempID == 30001492) || (tempID == 30001493) || (tempID == 30001494) || (tempID == 30001495) || (tempID == 

				30001496) || (tempID == 30001497) || (tempID == 30001498) || (tempID == 30001499) || (tempID == 30001500) || 

				(tempID == 30001501) || (tempID == 30001502) || (tempID == 30001503) || (tempID == 30001504) || (tempID == 

				30001505) || (tempID == 30001506) || (tempID == 30001507) || (tempID == 30001508) || (tempID == 30001509) || 

				(tempID == 30001510) || (tempID == 30001511) || (tempID == 30001512) || (tempID == 30001513) || (tempID == 

				30001514) || (tempID == 30001518) || (tempID == 30001519) || (tempID == 30001520) || (tempID == 30001521) || 

				(tempID == 30001522) || (tempID == 30001525) || (tempID == 30001526))writer.write(tempString + "\n"); else 

				if((tempID == 30001526) || (tempID == 30001527) || (tempID == 30001528) || (tempID == 30001529) || (tempID == 

				30001530) || (tempID == 30001531) || (tempID == 30001532) || (tempID == 30001533) || (tempID == 30001534) || 

				(tempID == 30001535) || (tempID == 30001536) || (tempID == 30001537) || (tempID == 30001538) || (tempID == 

				30001539) || (tempID == 30001540) || (tempID == 30001541) || (tempID == 30001542) || (tempID == 30001543) || 

				(tempID == 30001544) || (tempID == 30001545) || (tempID == 30001546) || (tempID == 30001547) || (tempID == 

				30001548) || (tempID == 30001549) || (tempID == 30001550) || (tempID == 30001551) || (tempID == 30001552) || 

				(tempID == 30001553) || (tempID == 30001554) || (tempID == 30001555) || (tempID == 30001556) || (tempID == 

				30001557) || (tempID == 30001558) || (tempID == 30001559) || (tempID == 30001560) || (tempID == 30001561) || 

				(tempID == 30001562) || (tempID == 30001563) || (tempID == 30001564) || (tempID == 30001565) || (tempID == 

				30001566) || (tempID == 30001567) || (tempID == 30001568) || (tempID == 30001569) || (tempID == 30001570) || 

				(tempID == 30001571) || (tempID == 30001572) || (tempID == 30001573) || (tempID == 30001574) || (tempID == 

				30001575) || (tempID == 30001576) || (tempID == 30001577) || (tempID == 30001578) || (tempID == 30001579) || 

				(tempID == 30001580) || (tempID == 30001581) || (tempID == 30001582) || (tempID == 30001583) || (tempID == 

				30001584) || (tempID == 30001585) || (tempID == 30001586) || (tempID == 30001587) || (tempID == 30001588) || 

				(tempID == 30001589) || (tempID == 30001590) || (tempID == 30001591) || (tempID == 

				30001592))writer.write(tempString + "\n"); else if((tempID == 30001592) || (tempID == 30001593) || (tempID == 

				30001594) || (tempID == 30001595) || (tempID == 30001596) || (tempID == 30001597) || (tempID == 30001598) || 

				(tempID == 30001599) || (tempID == 30001600) || (tempID == 30001601) || (tempID == 30001602) || (tempID == 

				30001603) || (tempID == 30001604) || (tempID == 30001605) || (tempID == 30001606) || (tempID == 30001607) || 

				(tempID == 30001608) || (tempID == 30001609) || (tempID == 30001610) || (tempID == 30001611) || (tempID == 

				30001612) || (tempID == 30001613) || (tempID == 30001614) || (tempID == 30001615) || (tempID == 30001616) || 

				(tempID == 30001617) || (tempID == 30001618) || (tempID == 30001619) || (tempID == 30001620) || (tempID == 

				30001621) || (tempID == 30001622) || (tempID == 30001623) || (tempID == 30001624) || (tempID == 30001625) || 

				(tempID == 30001626) || (tempID == 30001627) || (tempID == 30001628) || (tempID == 30001629) || (tempID == 

				30001630) || (tempID == 30001631) || (tempID == 30001632) || (tempID == 30001633) || (tempID == 30001634) || 

				(tempID == 30001635) || (tempID == 30001636) || (tempID == 30001637) || (tempID == 30001638) || (tempID == 

				30001639) || (tempID == 30001640) || (tempID == 30001641) || (tempID == 30001642) || (tempID == 30001643) || 

				(tempID == 30001664) || (tempID == 30001668) || (tempID == 30001682) || (tempID == 30001683) || (tempID == 

				30001684) || (tempID == 30001685) || (tempID == 30001720) || (tempID == 30001721) || (tempID == 30001743) || 

				(tempID == 30001744) || (tempID == 30001745) || (tempID == 30001746) || (tempID == 30001747) || (tempID == 

				30001748) || (tempID == 30001749) || (tempID == 30001750) || (tempID == 30001751) || (tempID == 30001752) || 

				(tempID == 30001753) || (tempID == 30001754) || (tempID == 30001755) || (tempID == 

				30001756))writer.write(tempString + "\n"); else if((tempID == 30001756) || (tempID == 30001757) || (tempID == 

				30001758) || (tempID == 30001759) || (tempID == 30001760) || (tempID == 30001761) || (tempID == 30001762) || 

				(tempID == 30001763) || (tempID == 30001764) || (tempID == 30001765) || (tempID == 30001766) || (tempID == 

				30001767) || (tempID == 30001768) || (tempID == 30001769) || (tempID == 30001770) || (tempID == 30001771) || 

				(tempID == 30001772) || (tempID == 30001773) || (tempID == 30001774) || (tempID == 30001775) || (tempID == 

				30001776) || (tempID == 30001777) || (tempID == 30001778) || (tempID == 30001779) || (tempID == 30001780) || 

				(tempID == 30001781) || (tempID == 30001782) || (tempID == 30001783) || (tempID == 30001784) || (tempID == 

				30001785) || (tempID == 30001786) || (tempID == 30001787) || (tempID == 30001788) || (tempID == 30001789) || 

				(tempID == 30001790) || (tempID == 30001791) || (tempID == 30001792) || (tempID == 30001793) || (tempID == 

				30001794) || (tempID == 30001795) || (tempID == 30001796) || (tempID == 30001797) || (tempID == 30001798) || 

				(tempID == 30001799) || (tempID == 30001800) || (tempID == 30001801) || (tempID == 30001802) || (tempID == 

				30001803) || (tempID == 30001804) || (tempID == 30001805) || (tempID == 30001806) || (tempID == 30001807) || 

				(tempID == 30001808) || (tempID == 30001809) || (tempID == 30001810) || (tempID == 30001811) || (tempID == 

				30001812) || (tempID == 30001813) || (tempID == 30001814) || (tempID == 30001815) || (tempID == 30001816) || 

				(tempID == 30001817) || (tempID == 30001818) || (tempID == 30001819) || (tempID == 30001820) || (tempID == 

				30001821) || (tempID == 30001822))writer.write(tempString + "\n"); else if((tempID == 30001822) || (tempID == 

				30001823) || (tempID == 30001824) || (tempID == 30001825) || (tempID == 30001826) || (tempID == 30001827) || 

				(tempID == 30001828) || (tempID == 30001829) || (tempID == 30001830) || (tempID == 30001831) || (tempID == 

				30001832) || (tempID == 30001833) || (tempID == 30001834) || (tempID == 30001835) || (tempID == 30001836) || 

				(tempID == 30001837) || (tempID == 30001838) || (tempID == 30001839) || (tempID == 30001840) || (tempID == 

				30001841) || (tempID == 30001842) || (tempID == 30001843) || (tempID == 30001844) || (tempID == 30001845) || 

				(tempID == 30001846) || (tempID == 30001847) || (tempID == 30001848) || (tempID == 30001849) || (tempID == 

				30001850) || (tempID == 30001851) || (tempID == 30001852) || (tempID == 30001853) || (tempID == 30001854) || 

				(tempID == 30001855) || (tempID == 30001856) || (tempID == 30001857) || (tempID == 30001858) || (tempID == 

				30001859) || (tempID == 30001860) || (tempID == 30001861) || (tempID == 30001862) || (tempID == 30001863) || 

				(tempID == 30001864) || (tempID == 30001865) || (tempID == 30001866) || (tempID == 30001867) || (tempID == 

				30001868) || (tempID == 30001869) || (tempID == 30001870) || (tempID == 30001871) || (tempID == 30001872) || 

				(tempID == 30001873) || (tempID == 30001874) || (tempID == 30001875) || (tempID == 30001876) || (tempID == 

				30001877) || (tempID == 30001878) || (tempID == 30001879) || (tempID == 30001880) || (tempID == 30001881) || 

				(tempID == 30001882) || (tempID == 30001883) || (tempID == 30001884) || (tempID == 30001885) || (tempID == 

				30001886) || (tempID == 30001887) || (tempID == 30001888) || (tempID == 30001889))writer.write(tempString + 

				"\n"); else if((tempID == 30001889) || (tempID == 30001890) || (tempID == 30001891) || (tempID == 30001892) || 

				(tempID == 30001893) || (tempID == 30001894) || (tempID == 30001895) || (tempID == 30001896) || (tempID == 

				30001897) || (tempID == 30001898) || (tempID == 30001899) || (tempID == 30001900) || (tempID == 30001901) || 

				(tempID == 30001902) || (tempID == 30001903) || (tempID == 30001904) || (tempID == 30001905) || (tempID == 

				30001906) || (tempID == 30001907) || (tempID == 30001908) || (tempID == 30001909) || (tempID == 30001910) || 

				(tempID == 30001911) || (tempID == 30001912) || (tempID == 30001913) || (tempID == 30001914) || (tempID == 

				30001915) || (tempID == 30001916) || (tempID == 30001917) || (tempID == 30001918) || (tempID == 30001919) || 

				(tempID == 30001920) || (tempID == 30001921) || (tempID == 30001922) || (tempID == 30001923) || (tempID == 

				30001924) || (tempID == 30001925) || (tempID == 30001926) || (tempID == 30001927) || (tempID == 30001928) || 

				(tempID == 30001929) || (tempID == 30001930) || (tempID == 30001931) || (tempID == 30001932) || (tempID == 

				30001933) || (tempID == 30001934) || (tempID == 30001935) || (tempID == 30001936) || (tempID == 30001937) || 

				(tempID == 30001938) || (tempID == 30001939) || (tempID == 30001940) || (tempID == 30001941) || (tempID == 

				30001942) || (tempID == 30001943) || (tempID == 30001944) || (tempID == 30001945) || (tempID == 30001946) || 

				(tempID == 30001947) || (tempID == 30001948) || (tempID == 30001949) || (tempID == 30001950) || (tempID == 

				30001951) || (tempID == 30001952) || (tempID == 30001953) || (tempID == 30001954) || (tempID == 30001955) || 

				(tempID == 30001956) || (tempID == 30001957) || (tempID == 30001958) || (tempID == 

				30001959))writer.write(tempString + "\n"); else if((tempID == 30001959) || (tempID == 30001960) || (tempID == 

				30001961) || (tempID == 30001962) || (tempID == 30001963) || (tempID == 30001964) || (tempID == 30001965) || 

				(tempID == 30001966) || (tempID == 30001967) || (tempID == 30001968) || (tempID == 30001969) || (tempID == 

				30001970) || (tempID == 30001971) || (tempID == 30001972) || (tempID == 30001973) || (tempID == 30001974) || 

				(tempID == 30001975) || (tempID == 30001976) || (tempID == 30001977) || (tempID == 30001978) || (tempID == 

				30001979) || (tempID == 30001980) || (tempID == 30001981) || (tempID == 30001982) || (tempID == 30001983) || 

				(tempID == 30001984) || (tempID == 30001985) || (tempID == 30001986) || (tempID == 30001987) || (tempID == 

				30001988) || (tempID == 30001989) || (tempID == 30001990) || (tempID == 30001991) || (tempID == 30001992) || 

				(tempID == 30001993) || (tempID == 30001994) || (tempID == 30001995) || (tempID == 30001996) || (tempID == 

				30001997) || (tempID == 30001998) || (tempID == 30001999) || (tempID == 30002000) || (tempID == 30002001) || 

				(tempID == 30002002) || (tempID == 30002003) || (tempID == 30002004) || (tempID == 30002005) || (tempID == 

				30002006) || (tempID == 30002007) || (tempID == 30002008) || (tempID == 30002009) || (tempID == 30002010) || 

				(tempID == 30002011) || (tempID == 30002012) || (tempID == 30002013) || (tempID == 30002014) || (tempID == 

				30002015) || (tempID == 30002016) || (tempID == 30002017) || (tempID == 30002018) || (tempID == 30002019) || 

				(tempID == 30002020) || (tempID == 30002021) || (tempID == 30002022) || (tempID == 30002023) || (tempID == 

				30002024) || (tempID == 30002025) || (tempID == 30002026) || (tempID == 30002027) || (tempID == 30002028) || 

				(tempID == 30002029))writer.write(tempString + "\n"); else if((tempID == 30002029) || (tempID == 30002030) || 

				(tempID == 30002031) || (tempID == 30002032) || (tempID == 30002033) || (tempID == 30002034) || (tempID == 

				30002035) || (tempID == 30002036) || (tempID == 30002037) || (tempID == 30002038) || (tempID == 30002039) || 

				(tempID == 30002040) || (tempID == 30002041) || (tempID == 30002042) || (tempID == 30002043) || (tempID == 

				30002044) || (tempID == 30002045) || (tempID == 30002046) || (tempID == 30002047) || (tempID == 30002060) || 

				(tempID == 30002061) || (tempID == 30002062) || (tempID == 30002063) || (tempID == 30002064) || (tempID == 

				30002065) || (tempID == 30002066) || (tempID == 30002067) || (tempID == 30002076) || (tempID == 30002077) || 

				(tempID == 30002078) || (tempID == 30002079) || (tempID == 30002080) || (tempID == 30002081) || (tempID == 

				30002090) || (tempID == 30002091) || (tempID == 30002092) || (tempID == 30002093) || (tempID == 30002094) || 

				(tempID == 30002095) || (tempID == 30002096) || (tempID == 30002097) || (tempID == 30002098) || (tempID == 

				30002099) || (tempID == 30002100) || (tempID == 30002101) || (tempID == 30002102) || (tempID == 30002103) || 

				(tempID == 30002104) || (tempID == 30002105) || (tempID == 30002106) || (tempID == 30002107) || (tempID == 

				30002108) || (tempID == 30002109) || (tempID == 30002110) || (tempID == 30002111) || (tempID == 30002112) || 

				(tempID == 30002113) || (tempID == 30002114) || (tempID == 30002115) || (tempID == 30002116) || (tempID == 

				30002117) || (tempID == 30002118) || (tempID == 30002119) || (tempID == 30002120))writer.write(tempString + 

				"\n"); else if((tempID == 30002120) || (tempID == 30002121) || (tempID == 30002122) || (tempID == 30002123) || 

				(tempID == 30002124) || (tempID == 30002125) || (tempID == 30002126) || (tempID == 30002127) || (tempID == 

				30002128) || (tempID == 30002129) || (tempID == 30002130) || (tempID == 30002131) || (tempID == 30002132) || 

				(tempID == 30002133) || (tempID == 30002134) || (tempID == 30002135) || (tempID == 30002136) || (tempID == 

				30002137) || (tempID == 30002138) || (tempID == 30002139) || (tempID == 30002140) || (tempID == 30002141) || 

				(tempID == 30002142) || (tempID == 30002143) || (tempID == 30002144) || (tempID == 30002145) || (tempID == 

				30002146) || (tempID == 30002147) || (tempID == 30002148) || (tempID == 30002149) || (tempID == 30002150) || 

				(tempID == 30002151) || (tempID == 30002152) || (tempID == 30002153) || (tempID == 30002154) || (tempID == 

				30002155) || (tempID == 30002156) || (tempID == 30002157) || (tempID == 30002158) || (tempID == 30002159) || 

				(tempID == 30002160) || (tempID == 30002161) || (tempID == 30002162) || (tempID == 30002163) || (tempID == 

				30002164) || (tempID == 30002165) || (tempID == 30002166) || (tempID == 30002167) || (tempID == 30002168) || 

				(tempID == 30002169) || (tempID == 30002170) || (tempID == 30002171) || (tempID == 30002172) || (tempID == 

				30002173) || (tempID == 30002174) || (tempID == 30002175) || (tempID == 30002176) || (tempID == 30002177) || 

				(tempID == 30002178) || (tempID == 30002179) || (tempID == 30002180) || (tempID == 30002181) || (tempID == 

				30002182) || (tempID == 30002183) || (tempID == 30002184) || (tempID == 30002185) || (tempID == 30002186) || 

				(tempID == 30002236) || (tempID == 30002239) || (tempID == 30002240) || (tempID == 30002241) || (tempID == 

				30002256) || (tempID == 30002272) || (tempID == 30002283))writer.write(tempString + "\n"); else if((tempID == 

				30002283) || (tempID == 30002284) || (tempID == 30002285) || (tempID == 30002286) || (tempID == 30002287) || 

				(tempID == 30002288) || (tempID == 30002289) || (tempID == 30002290) || (tempID == 30002291) || (tempID == 

				30002292) || (tempID == 30002293) || (tempID == 30002294) || (tempID == 30002295) || (tempID == 30002296) || 

				(tempID == 30002297) || (tempID == 30002298) || (tempID == 30002299) || (tempID == 30002300) || (tempID == 

				30002301) || (tempID == 30002302) || (tempID == 30002303) || (tempID == 30002304) || (tempID == 30002305) || 

				(tempID == 30002306) || (tempID == 30002307) || (tempID == 30002308) || (tempID == 30002309) || (tempID == 

				30002310) || (tempID == 30002311) || (tempID == 30002312) || (tempID == 30002313) || (tempID == 30002314) || 

				(tempID == 30002315) || (tempID == 30002316) || (tempID == 30002317) || (tempID == 30002318) || (tempID == 

				30002319) || (tempID == 30002320) || (tempID == 30002321) || (tempID == 30002322) || (tempID == 30002323) || 

				(tempID == 30002324) || (tempID == 30002325) || (tempID == 30002326) || (tempID == 30002327) || (tempID == 

				30002328) || (tempID == 30002329) || (tempID == 30002330) || (tempID == 30002331) || (tempID == 30002332) || 

				(tempID == 30002333) || (tempID == 30002334) || (tempID == 30002335) || (tempID == 30002336) || (tempID == 

				30002337) || (tempID == 30002338) || (tempID == 30002339) || (tempID == 30002340) || (tempID == 30002341) || 

				(tempID == 30002342) || (tempID == 30002343) || (tempID == 30002344) || (tempID == 30002345) || (tempID == 

				30002346) || (tempID == 30002347) || (tempID == 30002348) || (tempID == 30002349) || (tempID == 30002350) || 

				(tempID == 30002351) || (tempID == 30002352) || (tempID == 30002353) || (tempID == 30002354) || (tempID == 

				30002355))writer.write(tempString + "\n"); else if((tempID == 30002355) || (tempID == 30002356) || (tempID == 

				30002357) || (tempID == 30002358) || (tempID == 30002359) || (tempID == 30002360) || (tempID == 30002361) || 

				(tempID == 30002362) || (tempID == 30002363) || (tempID == 30002364) || (tempID == 30002365) || (tempID == 

				30002366) || (tempID == 30002367) || (tempID == 30002368) || (tempID == 30002369) || (tempID == 30002370) || 

				(tempID == 30002371) || (tempID == 30002372) || (tempID == 30002373) || (tempID == 30002374) || (tempID == 

				30002375) || (tempID == 30002376) || (tempID == 30002377) || (tempID == 30002378) || (tempID == 30002379) || 

				(tempID == 30002380) || (tempID == 30002381) || (tempID == 30002382) || (tempID == 30002390) || (tempID == 

				30002391) || (tempID == 30002392) || (tempID == 30002393) || (tempID == 30002394) || (tempID == 30002395) || 

				(tempID == 30002396) || (tempID == 30002401) || (tempID == 30002402) || (tempID == 30002403) || (tempID == 

				30002404) || (tempID == 30002405) || (tempID == 30002406) || (tempID == 30002407) || (tempID == 30002409) || 

				(tempID == 30002410) || (tempID == 30002411) || (tempID == 30002412) || (tempID == 30002413) || (tempID == 

				30002414) || (tempID == 30002415) || (tempID == 30002418) || (tempID == 30002419) || (tempID == 30002420) || 

				(tempID == 30002421) || (tempID == 30002422) || (tempID == 30002423) || (tempID == 30002424) || (tempID == 

				30002425) || (tempID == 30002426) || (tempID == 30002427) || (tempID == 30002428) || (tempID == 30002429) || 

				(tempID == 30002430) || (tempID == 30002431) || (tempID == 30002432) || (tempID == 30002433) || (tempID == 

				30002434) || (tempID == 30002435) || (tempID == 30002436) || (tempID == 30002437) || (tempID == 

				30002438))writer.write(tempString + "\n"); else if((tempID == 30002438) || (tempID == 30002439) || (tempID == 

				30002440) || (tempID == 30002441) || (tempID == 30002442) || (tempID == 30002443) || (tempID == 30002444) || 

				(tempID == 30002445) || (tempID == 30002446) || (tempID == 30002447) || (tempID == 30002448) || (tempID == 

				30002449) || (tempID == 30002450) || (tempID == 30002451) || (tempID == 30002452) || (tempID == 30002453) || 

				(tempID == 30002454) || (tempID == 30002455) || (tempID == 30002456) || (tempID == 30002457) || (tempID == 

				30002458) || (tempID == 30002459) || (tempID == 30002460) || (tempID == 30002461) || (tempID == 30002462) || 

				(tempID == 30002463) || (tempID == 30002464) || (tempID == 30002465) || (tempID == 30002466) || (tempID == 

				30002467) || (tempID == 30002468) || (tempID == 30002469) || (tempID == 30002470) || (tempID == 30002471) || 

				(tempID == 30002472) || (tempID == 30002473) || (tempID == 30002474) || (tempID == 30002475) || (tempID == 

				30002476) || (tempID == 30002477) || (tempID == 30002478) || (tempID == 30002479) || (tempID == 30002480) || 

				(tempID == 30002481) || (tempID == 30002482) || (tempID == 30002483) || (tempID == 30002484) || (tempID == 

				30002485) || (tempID == 30002486) || (tempID == 30002487) || (tempID == 30002488) || (tempID == 30002489) || 

				(tempID == 30002490) || (tempID == 30002491) || (tempID == 30002492) || (tempID == 30002493) || (tempID == 

				30002494) || (tempID == 30002495) || (tempID == 30002496) || (tempID == 30002497) || (tempID == 30002498) || 

				(tempID == 30002499) || (tempID == 30002500) || (tempID == 30002501) || (tempID == 30002502) || (tempID == 

				30002503) || (tempID == 30002504) || (tempID == 30002514) || (tempID == 30002516) || (tempID == 30002539) || 

				(tempID == 30002540) || (tempID == 30002551))writer.write(tempString + "\n"); else if((tempID == 30002551) || 

				(tempID == 30002559) || (tempID == 30002560) || (tempID == 30002574) || (tempID == 30002575) || (tempID == 

				30002580) || (tempID == 30002581) || (tempID == 30002582) || (tempID == 30002583) || (tempID == 30002584) || 

				(tempID == 30002585) || (tempID == 30002586) || (tempID == 30002587) || (tempID == 30002588) || (tempID == 

				30002589) || (tempID == 30002590) || (tempID == 30002591) || (tempID == 30002592) || (tempID == 30002593) || 

				(tempID == 30002594) || (tempID == 30002595) || (tempID == 30002596) || (tempID == 30002597) || (tempID == 

				30002598) || (tempID == 30002599) || (tempID == 30002600) || (tempID == 30002601) || (tempID == 30002602) || 

				(tempID == 30002603) || (tempID == 30002604) || (tempID == 30002605) || (tempID == 30002606) || (tempID == 

				30002607) || (tempID == 30002608) || (tempID == 30002609) || (tempID == 30002610) || (tempID == 30002611) || 

				(tempID == 30002612) || (tempID == 30002613) || (tempID == 30002614) || (tempID == 30002615) || (tempID == 

				30002616) || (tempID == 30002617) || (tempID == 30002618) || (tempID == 30002619) || (tempID == 30002620) || 

				(tempID == 30002621) || (tempID == 30002622) || (tempID == 30002623) || (tempID == 30002624) || (tempID == 

				30002625) || (tempID == 30002626) || (tempID == 30002627) || (tempID == 30002628) || (tempID == 30002629) || 

				(tempID == 30002630) || (tempID == 30002631) || (tempID == 30002719) || (tempID == 30002720) || (tempID == 

				30002721) || (tempID == 30002722) || (tempID == 30002723) || (tempID == 30002725) || (tempID == 30002727) || 

				(tempID == 30002728) || (tempID == 30002729) || (tempID == 30002730) || (tempID == 30002758) || (tempID == 

				30002760))writer.write(tempString + "\n"); else if((tempID == 30002760) || (tempID == 30002806) || (tempID == 

				30002807) || (tempID == 30002809) || (tempID == 30002810) || (tempID == 30002811) || (tempID == 30002812) || 

				(tempID == 30002813) || (tempID == 30002820) || (tempID == 30002821) || (tempID == 30002822) || (tempID == 

				30002823) || (tempID == 30002824) || (tempID == 30002825) || (tempID == 30002826) || (tempID == 30002827) || 

				(tempID == 30002828) || (tempID == 30002829) || (tempID == 30002830) || (tempID == 30002831) || (tempID == 

				30002832) || (tempID == 30002833) || (tempID == 30002834) || (tempID == 30002835) || (tempID == 30002836) || 

				(tempID == 30002837) || (tempID == 30002838) || (tempID == 30002839) || (tempID == 30002840) || (tempID == 

				30002841) || (tempID == 30002842) || (tempID == 30002843) || (tempID == 30002844) || (tempID == 30002845) || 

				(tempID == 30002846) || (tempID == 30002847) || (tempID == 30002848) || (tempID == 30002849) || (tempID == 

				30002850) || (tempID == 30002851) || (tempID == 30002852) || (tempID == 30002853) || (tempID == 30002854) || 

				(tempID == 30002855) || (tempID == 30002856) || (tempID == 30002857) || (tempID == 30002858) || (tempID == 

				30002859) || (tempID == 30002860) || (tempID == 30002861) || (tempID == 30002862) || (tempID == 30002863) || 

				(tempID == 30002864) || (tempID == 30002865) || (tempID == 30002866) || (tempID == 30002867) || (tempID == 

				30002868) || (tempID == 30002869) || (tempID == 30002870) || (tempID == 30002871) || (tempID == 30002872) || 

				(tempID == 30002873) || (tempID == 30002874) || (tempID == 30002875) || (tempID == 30002876) || (tempID == 

				30002877) || (tempID == 30002878) || (tempID == 30002879) || (tempID == 30002880) || (tempID == 30002881) || 

				(tempID == 30002882))writer.write(tempString + "\n"); else if((tempID == 30002882) || (tempID == 30002883) || 

				(tempID == 30002884) || (tempID == 30002885) || (tempID == 30002886) || (tempID == 30002887) || (tempID == 

				30002888) || (tempID == 30002889) || (tempID == 30002890) || (tempID == 30002891) || (tempID == 30002892) || 

				(tempID == 30002893) || (tempID == 30002894) || (tempID == 30002895) || (tempID == 30002896) || (tempID == 

				30002897) || (tempID == 30002898) || (tempID == 30002899) || (tempID == 30002900) || (tempID == 30002901) || 

				(tempID == 30002902) || (tempID == 30002903) || (tempID == 30002904) || (tempID == 30002905) || (tempID == 

				30002906) || (tempID == 30002907) || (tempID == 30002908) || (tempID == 30002909) || (tempID == 30002910) || 

				(tempID == 30002911) || (tempID == 30002912) || (tempID == 30002913) || (tempID == 30002914) || (tempID == 

				30002915) || (tempID == 30002916) || (tempID == 30002917) || (tempID == 30002918) || (tempID == 30002919) || 

				(tempID == 30002920) || (tempID == 30002921) || (tempID == 30002922) || (tempID == 30002923) || (tempID == 

				30002924) || (tempID == 30002925) || (tempID == 30002926) || (tempID == 30002927) || (tempID == 30002928) || 

				(tempID == 30002929) || (tempID == 30002930) || (tempID == 30002931) || (tempID == 30002932) || (tempID == 

				30002933) || (tempID == 30002934) || (tempID == 30002935) || (tempID == 30002936) || (tempID == 30002937) || 

				(tempID == 30002938) || (tempID == 30002939) || (tempID == 30002940) || (tempID == 30002941) || (tempID == 

				30002942) || (tempID == 30002943) || (tempID == 30002944) || (tempID == 30002945) || (tempID == 30002946) || 

				(tempID == 30002947) || (tempID == 30002948))writer.write(tempString + "\n"); else if((tempID == 30002948) || 

				(tempID == 30002949) || (tempID == 30002950) || (tempID == 30002951) || (tempID == 30002952) || (tempID == 

				30002953) || (tempID == 30002954) || (tempID == 30002955) || (tempID == 30002956) || (tempID == 30002957) || 

				(tempID == 30002958) || (tempID == 30002959) || (tempID == 30002960) || (tempID == 30002961) || (tempID == 

				30002962) || (tempID == 30002979) || (tempID == 30002980) || (tempID == 30002983) || (tempID == 30002984) || 

				(tempID == 30002985) || (tempID == 30002987) || (tempID == 30003042) || (tempID == 30003057) || (tempID == 

				30003060) || (tempID == 30003061) || (tempID == 30003062) || (tempID == 30003086) || (tempID == 30003087) || 

				(tempID == 30003088) || (tempID == 30003089) || (tempID == 30003090) || (tempID == 30003091) || (tempID == 

				30003098) || (tempID == 30003099) || (tempID == 30003100) || (tempID == 30003101) || (tempID == 30003102) || 

				(tempID == 30003103) || (tempID == 30003104) || (tempID == 30003105) || (tempID == 30003106) || (tempID == 

				30003107) || (tempID == 30003108) || (tempID == 30003109) || (tempID == 30003110) || (tempID == 30003111) || 

				(tempID == 30003112) || (tempID == 30003113) || (tempID == 30003114) || (tempID == 30003115) || (tempID == 

				30003116) || (tempID == 30003117) || (tempID == 30003118) || (tempID == 30003119) || (tempID == 30003120) || 

				(tempID == 30003121) || (tempID == 30003122) || (tempID == 30003123) || (tempID == 30003124) || (tempID == 

				30003125) || (tempID == 30003126) || (tempID == 30003127) || (tempID == 30003128) || (tempID == 30003129) || 

				(tempID == 30003130) || (tempID == 30003131) || (tempID == 30003132))writer.write(tempString + "\n"); else 

				if((tempID == 30003132) || (tempID == 30003133) || (tempID == 30003134) || (tempID == 30003135) || (tempID == 

				30003136) || (tempID == 30003137) || (tempID == 30003138) || (tempID == 30003139) || (tempID == 30003140) || 

				(tempID == 30003141) || (tempID == 30003142) || (tempID == 30003143) || (tempID == 30003144) || (tempID == 

				30003145) || (tempID == 30003146) || (tempID == 30003147) || (tempID == 30003148) || (tempID == 30003149) || 

				(tempID == 30003150) || (tempID == 30003151) || (tempID == 30003152) || (tempID == 30003153) || (tempID == 

				30003154) || (tempID == 30003155) || (tempID == 30003156) || (tempID == 30003157) || (tempID == 30003158) || 

				(tempID == 30003159) || (tempID == 30003160) || (tempID == 30003161) || (tempID == 30003162) || (tempID == 

				30003163) || (tempID == 30003164) || (tempID == 30003165) || (tempID == 30003166) || (tempID == 30003167) || 

				(tempID == 30003168) || (tempID == 30003169) || (tempID == 30003170) || (tempID == 30003171) || (tempID == 

				30003172) || (tempID == 30003173) || (tempID == 30003174) || (tempID == 30003175) || (tempID == 30003176) || 

				(tempID == 30003177) || (tempID == 30003178) || (tempID == 30003179) || (tempID == 30003180) || (tempID == 

				30003181) || (tempID == 30003182) || (tempID == 30003183) || (tempID == 30003184) || (tempID == 30003185) || 

				(tempID == 30003186) || (tempID == 30003187) || (tempID == 30003188) || (tempID == 30003189) || (tempID == 

				30003190) || (tempID == 30003191) || (tempID == 30003192) || (tempID == 30003193) || (tempID == 30003194) || 

				(tempID == 30003195) || (tempID == 30003196) || (tempID == 30003197) || (tempID == 30003198) || (tempID == 

				30003199) || (tempID == 30003200) || (tempID == 30003201) || (tempID == 30003202) || (tempID == 

				30003203))writer.write(tempString + "\n"); else if((tempID == 30003203) || (tempID == 30003204) || (tempID == 

				30003205) || (tempID == 30003206) || (tempID == 30003207) || (tempID == 30003208) || (tempID == 30003209) || 

				(tempID == 30003210) || (tempID == 30003211) || (tempID == 30003212) || (tempID == 30003213) || (tempID == 

				30003214) || (tempID == 30003215) || (tempID == 30003216) || (tempID == 30003217) || (tempID == 30003218) || 

				(tempID == 30003219) || (tempID == 30003220) || (tempID == 30003221) || (tempID == 30003222) || (tempID == 

				30003223) || (tempID == 30003224) || (tempID == 30003225) || (tempID == 30003226) || (tempID == 30003227) || 

				(tempID == 30003228) || (tempID == 30003229) || (tempID == 30003230) || (tempID == 30003231) || (tempID == 

				30003232) || (tempID == 30003233) || (tempID == 30003234) || (tempID == 30003235) || (tempID == 30003236) || 

				(tempID == 30003237) || (tempID == 30003238) || (tempID == 30003239) || (tempID == 30003240) || (tempID == 

				30003241) || (tempID == 30003242) || (tempID == 30003243) || (tempID == 30003244) || (tempID == 30003245) || 

				(tempID == 30003246) || (tempID == 30003247) || (tempID == 30003248) || (tempID == 30003249) || (tempID == 

				30003250) || (tempID == 30003251) || (tempID == 30003252) || (tempID == 30003253) || (tempID == 30003254) || 

				(tempID == 30003255) || (tempID == 30003256) || (tempID == 30003257) || (tempID == 30003258) || (tempID == 

				30003259) || (tempID == 30003260) || (tempID == 30003261) || (tempID == 30003262) || (tempID == 30003263) || 

				(tempID == 30003264) || (tempID == 30003265) || (tempID == 30003266) || (tempID == 30003267) || (tempID == 

				30003268) || (tempID == 30003269) || (tempID == 30003270) || (tempID == 30003271) || (tempID == 

				30003272))writer.write(tempString + "\n"); else if((tempID == 30003272) || (tempID == 30003273) || (tempID == 

				30003274) || (tempID == 30003275) || (tempID == 30003276) || (tempID == 30003277) || (tempID == 30003278) || 

				(tempID == 30003279) || (tempID == 30003280) || (tempID == 30003281) || (tempID == 30003282) || (tempID == 

				30003283) || (tempID == 30003284) || (tempID == 30003285) || (tempID == 30003286) || (tempID == 30003287) || 

				(tempID == 30003288) || (tempID == 30003289) || (tempID == 30003290) || (tempID == 30003291) || (tempID == 

				30003292) || (tempID == 30003293) || (tempID == 30003294) || (tempID == 30003295) || (tempID == 30003296) || 

				(tempID == 30003297) || (tempID == 30003298) || (tempID == 30003299) || (tempID == 30003300) || (tempID == 

				30003301) || (tempID == 30003302) || (tempID == 30003303) || (tempID == 30003304) || (tempID == 30003305) || 

				(tempID == 30003306) || (tempID == 30003307) || (tempID == 30003308) || (tempID == 30003309) || (tempID == 

				30003310) || (tempID == 30003311) || (tempID == 30003312) || (tempID == 30003313) || (tempID == 30003314) || 

				(tempID == 30003315) || (tempID == 30003316) || (tempID == 30003317) || (tempID == 30003318) || (tempID == 

				30003319) || (tempID == 30003320) || (tempID == 30003321) || (tempID == 30003322) || (tempID == 30003323) || 

				(tempID == 30003324) || (tempID == 30003325) || (tempID == 30003326) || (tempID == 30003327) || (tempID == 

				30003328) || (tempID == 30003329) || (tempID == 30003330) || (tempID == 30003331) || (tempID == 30003332) || 

				(tempID == 30003333) || (tempID == 30003334) || (tempID == 30003335) || (tempID == 30003336) || (tempID == 

				30003337) || (tempID == 30003338) || (tempID == 30003339) || (tempID == 30003340) || (tempID == 30003341) || 

				(tempID == 30003342))writer.write(tempString + "\n"); else if((tempID == 30003342) || (tempID == 30003343) || 

				(tempID == 30003344) || (tempID == 30003345) || (tempID == 30003346) || (tempID == 30003347) || (tempID == 

				30003348) || (tempID == 30003349) || (tempID == 30003350) || (tempID == 30003351) || (tempID == 30003352) || 

				(tempID == 30003353) || (tempID == 30003354) || (tempID == 30003355) || (tempID == 30003356) || (tempID == 

				30003357) || (tempID == 30003358) || (tempID == 30003359) || (tempID == 30003360) || (tempID == 30003361) || 

				(tempID == 30003362) || (tempID == 30003363) || (tempID == 30003364) || (tempID == 30003365) || (tempID == 

				30003366) || (tempID == 30003367) || (tempID == 30003368) || (tempID == 30003369) || (tempID == 30003370) || 

				(tempID == 30003371) || (tempID == 30003372) || (tempID == 30003373) || (tempID == 30003444) || (tempID == 

				30003446) || (tempID == 30003465) || (tempID == 30003470) || (tempID == 30003475) || (tempID == 30003477) || 

				(tempID == 30003478) || (tempID == 30003479) || (tempID == 30003480) || (tempID == 30003483) || (tempID == 

				30003484) || (tempID == 30003557) || (tempID == 30003559) || (tempID == 30003560) || (tempID == 30003561) || 

				(tempID == 30003562) || (tempID == 30003563) || (tempID == 30003564) || (tempID == 30003565) || (tempID == 

				30003566) || (tempID == 30003568) || (tempID == 30003569) || (tempID == 30003570) || (tempID == 30003571) || 

				(tempID == 30003572) || (tempID == 30003585) || (tempID == 30003587) || (tempID == 30003594) || (tempID == 

				30003595) || (tempID == 30003596) || (tempID == 30003597) || (tempID == 30003598) || (tempID == 30003599) || 

				(tempID == 30003600) || (tempID == 30003601) || (tempID == 30003607) || (tempID == 

				30003608))writer.write(tempString + "\n"); else if((tempID == 30003608) || (tempID == 30003609) || (tempID == 

				30003610) || (tempID == 30003611) || (tempID == 30003612) || (tempID == 30003613) || (tempID == 30003614) || 

				(tempID == 30003615) || (tempID == 30003616) || (tempID == 30003617) || (tempID == 30003618) || (tempID == 

				30003619) || (tempID == 30003620) || (tempID == 30003621) || (tempID == 30003622) || (tempID == 30003623) || 

				(tempID == 30003624) || (tempID == 30003625) || (tempID == 30003626) || (tempID == 30003627) || (tempID == 

				30003628) || (tempID == 30003629) || (tempID == 30003630) || (tempID == 30003631) || (tempID == 30003632) || 

				(tempID == 30003633) || (tempID == 30003634) || (tempID == 30003635) || (tempID == 30003636) || (tempID == 

				30003637) || (tempID == 30003638) || (tempID == 30003639) || (tempID == 30003640) || (tempID == 30003641) || 

				(tempID == 30003642) || (tempID == 30003643) || (tempID == 30003644) || (tempID == 30003645) || (tempID == 

				30003646) || (tempID == 30003647) || (tempID == 30003648) || (tempID == 30003649) || (tempID == 30003650) || 

				(tempID == 30003651) || (tempID == 30003652) || (tempID == 30003653) || (tempID == 30003654) || (tempID == 

				30003655) || (tempID == 30003656) || (tempID == 30003657) || (tempID == 30003658) || (tempID == 30003659) || 

				(tempID == 30003660) || (tempID == 30003661) || (tempID == 30003662) || (tempID == 30003663) || (tempID == 

				30003664) || (tempID == 30003665) || (tempID == 30003666) || (tempID == 30003667) || (tempID == 30003668) || 

				(tempID == 30003669) || (tempID == 30003670) || (tempID == 30003671) || (tempID == 30003672) || (tempID == 

				30003673) || (tempID == 30003674) || (tempID == 30003675) || (tempID == 30003676) || (tempID == 30003677) || 

				(tempID == 30003678) || (tempID == 30003679) || (tempID == 30003680) || (tempID == 30003681) || (tempID == 

				30003682) || (tempID == 30003683) || (tempID == 30003684) || (tempID == 30003685) || (tempID == 30003686) || 

				(tempID == 30003687))writer.write(tempString + "\n"); else if((tempID == 30003687) || (tempID == 30003688) || 

				(tempID == 30003689) || (tempID == 30003690) || (tempID == 30003691) || (tempID == 30003692) || (tempID == 

				30003693) || (tempID == 30003694) || (tempID == 30003695) || (tempID == 30003696) || (tempID == 30003697) || 

				(tempID == 30003698) || (tempID == 30003699) || (tempID == 30003700) || (tempID == 30003701) || (tempID == 

				30003702) || (tempID == 30003703) || (tempID == 30003704) || (tempID == 30003705) || (tempID == 30003706) || 

				(tempID == 30003707) || (tempID == 30003708) || (tempID == 30003709) || (tempID == 30003710) || (tempID == 

				30003711) || (tempID == 30003712) || (tempID == 30003713) || (tempID == 30003714) || (tempID == 30003715) || 

				(tempID == 30003716) || (tempID == 30003717) || (tempID == 30003718) || (tempID == 30003719) || (tempID == 

				30003720) || (tempID == 30003721) || (tempID == 30003722) || (tempID == 30003723) || (tempID == 30003724) || 

				(tempID == 30003725) || (tempID == 30003726) || (tempID == 30003727) || (tempID == 30003728) || (tempID == 

				30003729) || (tempID == 30003730) || (tempID == 30003731) || (tempID == 30003732) || (tempID == 30003733) || 

				(tempID == 30003734) || (tempID == 30003735) || (tempID == 30003736) || (tempID == 30003737) || (tempID == 

				30003738) || (tempID == 30003739) || (tempID == 30003740) || (tempID == 30003741) || (tempID == 30003742) || 

				(tempID == 30003743) || (tempID == 30003744) || (tempID == 30003745) || (tempID == 30003746) || (tempID == 

				30003747) || (tempID == 30003748) || (tempID == 30003749) || (tempID == 30003750) || (tempID == 30003751) || 

				(tempID == 30003752) || (tempID == 30003753) || (tempID == 30003754) || (tempID == 30003755) || (tempID == 

				30003756) || (tempID == 30003757))writer.write(tempString + "\n"); else if((tempID == 30003757) || (tempID == 

				30003758) || (tempID == 30003759) || (tempID == 30003760) || (tempID == 30003761) || (tempID == 30003762) || 

				(tempID == 30003763) || (tempID == 30003764) || (tempID == 30003765) || (tempID == 30003766) || (tempID == 

				30003767) || (tempID == 30003768) || (tempID == 30003769) || (tempID == 30003770) || (tempID == 30003771) || 

				(tempID == 30003772) || (tempID == 30003773) || (tempID == 30003774) || (tempID == 30003775) || (tempID == 

				30003776) || (tempID == 30003777) || (tempID == 30003778) || (tempID == 30003779) || (tempID == 30003780) || 

				(tempID == 30003781) || (tempID == 30003782) || (tempID == 30003783) || (tempID == 30003784) || (tempID == 

				30003785) || (tempID == 30003786) || (tempID == 30003787) || (tempID == 30003788) || (tempID == 30003789) || 

				(tempID == 30003790) || (tempID == 30003791) || (tempID == 30003792) || (tempID == 30003793) || (tempID == 

				30003796) || (tempID == 30003797) || (tempID == 30003799) || (tempID == 30003800) || (tempID == 30003801) || 

				(tempID == 30003802) || (tempID == 30003803) || (tempID == 30003804) || (tempID == 30003805) || (tempID == 

				30003806) || (tempID == 30003808) || (tempID == 30003818) || (tempID == 30003819) || (tempID == 30003820) || 

				(tempID == 30003821) || (tempID == 30003822) || (tempID == 30003823) || (tempID == 30003829) || (tempID == 

				30003833) || (tempID == 30003835) || (tempID == 30003836) || (tempID == 30003838) || (tempID == 30003840) || 

				(tempID == 30003841) || (tempID == 30003842) || (tempID == 30003844) || (tempID == 30003845) || (tempID == 

				30003846) || (tempID == 30003847) || (tempID == 30003850) || (tempID == 30003851) || (tempID == 30003852) || 

				(tempID == 30003853) || (tempID == 30003854) || (tempID == 30003855) || (tempID == 

				30003856))writer.write(tempString + "\n"); else if((tempID == 30003856) || (tempID == 30003857) || (tempID == 

				30003887) || (tempID == 30003896) || (tempID == 30003897) || (tempID == 30003898) || (tempID == 30003899) || 

				(tempID == 30003900) || (tempID == 30003901) || (tempID == 30003902) || (tempID == 30003917) || (tempID == 

				30003918) || (tempID == 30003919) || (tempID == 30003920) || (tempID == 30003921) || (tempID == 30003922) || 

				(tempID == 30003923) || (tempID == 30003924) || (tempID == 30003925) || (tempID == 30003926) || (tempID == 

				30003927) || (tempID == 30003928) || (tempID == 30003930) || (tempID == 30003931) || (tempID == 30003932) || 

				(tempID == 30003933) || (tempID == 30003934) || (tempID == 30003935) || (tempID == 30003936) || (tempID == 

				30003937) || (tempID == 30003938) || (tempID == 30003939) || (tempID == 30003940) || (tempID == 30003941) || 

				(tempID == 30003942) || (tempID == 30003943) || (tempID == 30003944) || (tempID == 30003945) || (tempID == 

				30003946) || (tempID == 30003947) || (tempID == 30003948) || (tempID == 30003949) || (tempID == 30003950) || 

				(tempID == 30003951) || (tempID == 30003952) || (tempID == 30003953) || (tempID == 30003954) || (tempID == 

				30003955) || (tempID == 30003956) || (tempID == 30003957) || (tempID == 30003958) || (tempID == 30003959) || 

				(tempID == 30003960) || (tempID == 30003961) || (tempID == 30003962) || (tempID == 30003963) || (tempID == 

				30003964) || (tempID == 30003965) || (tempID == 30003966) || (tempID == 30003967) || (tempID == 30003968) || 

				(tempID == 30003969) || (tempID == 30003970) || (tempID == 30003971) || (tempID == 30003972) || (tempID == 

				30003973) || (tempID == 30003974) || (tempID == 30003975) || (tempID == 30003976) || (tempID == 30003977) || 

				(tempID == 30003978) || (tempID == 30003979))writer.write(tempString + "\n"); else if((tempID == 30003979) || 

				(tempID == 30003980) || (tempID == 30003981) || (tempID == 30003982) || (tempID == 30003983) || (tempID == 

				30003984) || (tempID == 30003985) || (tempID == 30003986) || (tempID == 30003987) || (tempID == 30003988) || 

				(tempID == 30003989) || (tempID == 30003990) || (tempID == 30003991) || (tempID == 30003992) || (tempID == 

				30003993) || (tempID == 30003994) || (tempID == 30003995) || (tempID == 30003996) || (tempID == 30003997) || 

				(tempID == 30003998) || (tempID == 30003999) || (tempID == 30004000) || (tempID == 30004001) || (tempID == 

				30004002) || (tempID == 30004003) || (tempID == 30004004) || (tempID == 30004005) || (tempID == 30004006) || 

				(tempID == 30004007) || (tempID == 30004008) || (tempID == 30004009) || (tempID == 30004010) || (tempID == 

				30004011) || (tempID == 30004012) || (tempID == 30004013) || (tempID == 30004014) || (tempID == 30004015) || 

				(tempID == 30004016) || (tempID == 30004017) || (tempID == 30004018) || (tempID == 30004019) || (tempID == 

				30004020) || (tempID == 30004021) || (tempID == 30004022) || (tempID == 30004023) || (tempID == 30004024) || 

				(tempID == 30004025) || (tempID == 30004026) || (tempID == 30004027) || (tempID == 30004028) || (tempID == 

				30004029) || (tempID == 30004030) || (tempID == 30004031) || (tempID == 30004032) || (tempID == 30004033) || 

				(tempID == 30004034) || (tempID == 30004035) || (tempID == 30004036) || (tempID == 30004037) || (tempID == 

				30004038) || (tempID == 30004039) || (tempID == 30004040) || (tempID == 30004041) || (tempID == 30004042) || 

				(tempID == 30004043) || (tempID == 30004044) || (tempID == 30004045) || (tempID == 30004046) || (tempID == 

				30004047) || (tempID == 30004048) || (tempID == 30004049))writer.write(tempString + "\n"); else if((tempID == 

				30004049) || (tempID == 30004050) || (tempID == 30004051) || (tempID == 30004052) || (tempID == 30004053) || 

				(tempID == 30004054) || (tempID == 30004055) || (tempID == 30004056) || (tempID == 30004057) || (tempID == 

				30004058) || (tempID == 30004059) || (tempID == 30004060) || (tempID == 30004061) || (tempID == 30004062) || 

				(tempID == 30004063) || (tempID == 30004064) || (tempID == 30004065) || (tempID == 30004066) || (tempID == 

				30004067) || (tempID == 30004068) || (tempID == 30004069) || (tempID == 30004070) || (tempID == 30004071) || 

				(tempID == 30004072) || (tempID == 30004073) || (tempID == 30004074) || (tempID == 30004075) || (tempID == 

				30004076) || (tempID == 30004108) || (tempID == 30004136) || (tempID == 30004137) || (tempID == 30004138) || 

				(tempID == 30004141) || (tempID == 30004161) || (tempID == 30004162) || (tempID == 30004163) || (tempID == 

				30004164) || (tempID == 30004165) || (tempID == 30004166) || (tempID == 30004167) || (tempID == 30004168) || 

				(tempID == 30004169) || (tempID == 30004170) || (tempID == 30004171) || (tempID == 30004172) || (tempID == 

				30004173) || (tempID == 30004174) || (tempID == 30004175) || (tempID == 30004176) || (tempID == 30004177) || 

				(tempID == 30004178) || (tempID == 30004179) || (tempID == 30004180) || (tempID == 30004181) || (tempID == 

				30004182) || (tempID == 30004183) || (tempID == 30004184) || (tempID == 30004185) || (tempID == 30004186) || 

				(tempID == 30004187) || (tempID == 30004188) || (tempID == 30004189) || (tempID == 30004190) || (tempID == 

				30004191) || (tempID == 30004192) || (tempID == 30004193) || (tempID == 30004194) || (tempID == 30004195) || 

				(tempID == 30004196))writer.write(tempString + "\n"); else if((tempID == 30004196) || (tempID == 30004197) || 

				(tempID == 30004198) || (tempID == 30004199) || (tempID == 30004200) || (tempID == 30004201) || (tempID == 

				30004202) || (tempID == 30004203) || (tempID == 30004204) || (tempID == 30004205) || (tempID == 30004206) || 

				(tempID == 30004207) || (tempID == 30004208) || (tempID == 30004209) || (tempID == 30004210) || (tempID == 

				30004211) || (tempID == 30004212) || (tempID == 30004213) || (tempID == 30004214) || (tempID == 30004215) || 

				(tempID == 30004216) || (tempID == 30004217) || (tempID == 30004218) || (tempID == 30004219) || (tempID == 

				30004220) || (tempID == 30004221) || (tempID == 30004222) || (tempID == 30004223) || (tempID == 30004224) || 

				(tempID == 30004225) || (tempID == 30004226) || (tempID == 30004227) || (tempID == 30004228) || (tempID == 

				30004229) || (tempID == 30004230) || (tempID == 30004231) || (tempID == 30004232) || (tempID == 30004233) || 

				(tempID == 30004234) || (tempID == 30004235) || (tempID == 30004236) || (tempID == 30004237) || (tempID == 

				30004238) || (tempID == 30004239) || (tempID == 30004241) || (tempID == 30004243) || (tempID == 30004247) || 

				(tempID == 30004254) || (tempID == 30004255) || (tempID == 30004256) || (tempID == 30004257) || (tempID == 

				30004258) || (tempID == 30004259) || (tempID == 30004260) || (tempID == 30004261) || (tempID == 30004262) || 

				(tempID == 30004263) || (tempID == 30004264) || (tempID == 30004265) || (tempID == 30004266) || (tempID == 

				30004267) || (tempID == 30004271) || (tempID == 30004272) || (tempID == 30004273) || (tempID == 30004274) || 

				(tempID == 30004275) || (tempID == 30004276) || (tempID == 30004277) || (tempID == 30004278) || (tempID == 

				30004279) || (tempID == 30004280) || (tempID == 30004281))writer.write(tempString + "\n"); else if((tempID == 

				30004281) || (tempID == 30004282) || (tempID == 30004283) || (tempID == 30004284) || (tempID == 30004285) || 

				(tempID == 30004286) || (tempID == 30004287) || (tempID == 30004289) || (tempID == 30004291) || (tempID == 

				30004292) || (tempID == 30004294) || (tempID == 30004296) || (tempID == 30004297) || (tempID == 30004298) || 

				(tempID == 30004299) || (tempID == 30004300) || (tempID == 30004301) || (tempID == 30004302) || (tempID == 

				30004303) || (tempID == 30004304) || (tempID == 30004305) || (tempID == 30004306) || (tempID == 30004307) || 

				(tempID == 30004308) || (tempID == 30004309) || (tempID == 30004310) || (tempID == 30004311) || (tempID == 

				30004312) || (tempID == 30004313) || (tempID == 30004314) || (tempID == 30004315) || (tempID == 30004316) || 

				(tempID == 30004317) || (tempID == 30004318) || (tempID == 30004319) || (tempID == 30004320) || (tempID == 

				30004321) || (tempID == 30004322) || (tempID == 30004323) || (tempID == 30004324) || (tempID == 30004325) || 

				(tempID == 30004326) || (tempID == 30004327) || (tempID == 30004328) || (tempID == 30004329) || (tempID == 

				30004330) || (tempID == 30004331) || (tempID == 30004332) || (tempID == 30004333) || (tempID == 30004334) || 

				(tempID == 30004335) || (tempID == 30004336) || (tempID == 30004337) || (tempID == 30004338) || (tempID == 

				30004339) || (tempID == 30004340) || (tempID == 30004341) || (tempID == 30004342) || (tempID == 30004343) || 

				(tempID == 30004344) || (tempID == 30004345) || (tempID == 30004346) || (tempID == 30004347) || (tempID == 

				30004348) || (tempID == 30004349) || (tempID == 30004350) || (tempID == 30004351) || (tempID == 30004352) || 

				(tempID == 30004353) || (tempID == 30004354))writer.write(tempString + "\n"); else if((tempID == 30004354) || 

				(tempID == 30004355) || (tempID == 30004356) || (tempID == 30004357) || (tempID == 30004358) || (tempID == 

				30004359) || (tempID == 30004360) || (tempID == 30004361) || (tempID == 30004362) || (tempID == 30004363) || 

				(tempID == 30004364) || (tempID == 30004365) || (tempID == 30004366) || (tempID == 30004367) || (tempID == 

				30004368) || (tempID == 30004369) || (tempID == 30004370) || (tempID == 30004371) || (tempID == 30004372) || 

				(tempID == 30004373) || (tempID == 30004374) || (tempID == 30004375) || (tempID == 30004376) || (tempID == 

				30004377) || (tempID == 30004378) || (tempID == 30004379) || (tempID == 30004380) || (tempID == 30004381) || 

				(tempID == 30004382) || (tempID == 30004383) || (tempID == 30004384) || (tempID == 30004385) || (tempID == 

				30004386) || (tempID == 30004387) || (tempID == 30004388) || (tempID == 30004389) || (tempID == 30004390) || 

				(tempID == 30004391) || (tempID == 30004392) || (tempID == 30004393) || (tempID == 30004394) || (tempID == 

				30004395) || (tempID == 30004396) || (tempID == 30004397) || (tempID == 30004398) || (tempID == 30004399) || 

				(tempID == 30004400) || (tempID == 30004401) || (tempID == 30004402) || (tempID == 30004403) || (tempID == 

				30004404) || (tempID == 30004405) || (tempID == 30004406) || (tempID == 30004407) || (tempID == 30004408) || 

				(tempID == 30004409) || (tempID == 30004410) || (tempID == 30004411) || (tempID == 30004412) || (tempID == 

				30004413) || (tempID == 30004414) || (tempID == 30004415) || (tempID == 30004416) || (tempID == 30004417) || 

				(tempID == 30004418) || (tempID == 30004419) || (tempID == 30004420) || (tempID == 30004421) || (tempID == 

				30004422) || (tempID == 30004423) || (tempID == 30004424) || (tempID == 30004425) || (tempID == 30004426) || 

				(tempID == 30004427) || (tempID == 30004428))writer.write(tempString + "\n"); else if((tempID == 30004428) || 

				(tempID == 30004429) || (tempID == 30004430) || (tempID == 30004431) || (tempID == 30004432) || (tempID == 

				30004433) || (tempID == 30004434) || (tempID == 30004435) || (tempID == 30004436) || (tempID == 30004437) || 

				(tempID == 30004438) || (tempID == 30004439) || (tempID == 30004440) || (tempID == 30004441) || (tempID == 

				30004442) || (tempID == 30004443) || (tempID == 30004444) || (tempID == 30004445) || (tempID == 30004446) || 

				(tempID == 30004447) || (tempID == 30004448) || (tempID == 30004449) || (tempID == 30004450) || (tempID == 

				30004451) || (tempID == 30004452) || (tempID == 30004453) || (tempID == 30004454) || (tempID == 30004455) || 

				(tempID == 30004456) || (tempID == 30004457) || (tempID == 30004458) || (tempID == 30004459) || (tempID == 

				30004460) || (tempID == 30004461) || (tempID == 30004462) || (tempID == 30004463) || (tempID == 30004464) || 

				(tempID == 30004465) || (tempID == 30004466) || (tempID == 30004467) || (tempID == 30004468) || (tempID == 

				30004469) || (tempID == 30004470) || (tempID == 30004471) || (tempID == 30004472) || (tempID == 30004473) || 

				(tempID == 30004474) || (tempID == 30004475) || (tempID == 30004476) || (tempID == 30004477) || (tempID == 

				30004478) || (tempID == 30004479) || (tempID == 30004480) || (tempID == 30004481) || (tempID == 30004482) || 

				(tempID == 30004483) || (tempID == 30004484) || (tempID == 30004485) || (tempID == 30004486) || (tempID == 

				30004487) || (tempID == 30004488) || (tempID == 30004489) || (tempID == 30004490) || (tempID == 30004491) || 

				(tempID == 30004492) || (tempID == 30004493) || (tempID == 30004494) || (tempID == 30004495) || (tempID == 

				30004496) || (tempID == 30004497) || (tempID == 30004498) || (tempID == 30004499))writer.write(tempString + 

				"\n"); else if((tempID == 30004499) || (tempID == 30004500) || (tempID == 30004501) || (tempID == 30004502) || 

				(tempID == 30004503) || (tempID == 30004504) || (tempID == 30004505) || (tempID == 30004506) || (tempID == 

				30004507) || (tempID == 30004508) || (tempID == 30004509) || (tempID == 30004510) || (tempID == 30004511) || 

				(tempID == 30004512) || (tempID == 30004513) || (tempID == 30004514) || (tempID == 30004515) || (tempID == 

				30004516) || (tempID == 30004517) || (tempID == 30004518) || (tempID == 30004519) || (tempID == 30004520) || 

				(tempID == 30004521) || (tempID == 30004522) || (tempID == 30004523) || (tempID == 30004524) || (tempID == 

				30004525) || (tempID == 30004526) || (tempID == 30004527) || (tempID == 30004528) || (tempID == 30004529) || 

				(tempID == 30004530) || (tempID == 30004531) || (tempID == 30004532) || (tempID == 30004533) || (tempID == 

				30004534) || (tempID == 30004535) || (tempID == 30004536) || (tempID == 30004537) || (tempID == 30004538) || 

				(tempID == 30004539) || (tempID == 30004540) || (tempID == 30004541) || (tempID == 30004542) || (tempID == 

				30004543) || (tempID == 30004544) || (tempID == 30004545) || (tempID == 30004546) || (tempID == 30004547) || 

				(tempID == 30004548) || (tempID == 30004549) || (tempID == 30004550) || (tempID == 30004551) || (tempID == 

				30004552) || (tempID == 30004553) || (tempID == 30004554) || (tempID == 30004555) || (tempID == 30004556) || 

				(tempID == 30004557) || (tempID == 30004558) || (tempID == 30004559) || (tempID == 30004560) || (tempID == 

				30004561) || (tempID == 30004562) || (tempID == 30004563) || (tempID == 30004564) || (tempID == 30004565) || 

				(tempID == 30004566) || (tempID == 30004567) || (tempID == 30004568) || (tempID == 30004569) || (tempID == 

				30004570) || (tempID == 30004571))writer.write(tempString + "\n"); else if((tempID == 30004571) || (tempID == 

				30004572) || (tempID == 30004573) || (tempID == 30004574) || (tempID == 30004575) || (tempID == 30004576) || 

				(tempID == 30004577) || (tempID == 30004578) || (tempID == 30004579) || (tempID == 30004580) || (tempID == 

				30004581) || (tempID == 30004582) || (tempID == 30004583) || (tempID == 30004584) || (tempID == 30004585) || 

				(tempID == 30004586) || (tempID == 30004587) || (tempID == 30004588) || (tempID == 30004589) || (tempID == 

				30004590) || (tempID == 30004591) || (tempID == 30004592) || (tempID == 30004593) || (tempID == 30004594) || 

				(tempID == 30004595) || (tempID == 30004596) || (tempID == 30004597) || (tempID == 30004598) || (tempID == 

				30004599) || (tempID == 30004600) || (tempID == 30004601) || (tempID == 30004602) || (tempID == 30004603) || 

				(tempID == 30004604) || (tempID == 30004605) || (tempID == 30004606) || (tempID == 30004607) || (tempID == 

				30004608) || (tempID == 30004609) || (tempID == 30004610) || (tempID == 30004611) || (tempID == 30004612) || 

				(tempID == 30004613) || (tempID == 30004614) || (tempID == 30004615) || (tempID == 30004616) || (tempID == 

				30004617) || (tempID == 30004618) || (tempID == 30004619) || (tempID == 30004620) || (tempID == 30004621) || 

				(tempID == 30004622) || (tempID == 30004623) || (tempID == 30004624) || (tempID == 30004625) || (tempID == 

				30004626) || (tempID == 30004627) || (tempID == 30004628) || (tempID == 30004629) || (tempID == 30004630) || 

				(tempID == 30004631) || (tempID == 30004632) || (tempID == 30004633) || (tempID == 30004634) || (tempID == 

				30004635) || (tempID == 30004636) || (tempID == 30004637) || (tempID == 30004638) || (tempID == 30004639) || 

				(tempID == 30004640))writer.write(tempString + "\n"); else if((tempID == 30004640) || (tempID == 30004641) || 

				(tempID == 30004642) || (tempID == 30004643) || (tempID == 30004644) || (tempID == 30004645) || (tempID == 

				30004646) || (tempID == 30004647) || (tempID == 30004648) || (tempID == 30004649) || (tempID == 30004650) || 

				(tempID == 30004651) || (tempID == 30004652) || (tempID == 30004653) || (tempID == 30004654) || (tempID == 

				30004655) || (tempID == 30004656) || (tempID == 30004657) || (tempID == 30004658) || (tempID == 30004659) || 

				(tempID == 30004660) || (tempID == 30004661) || (tempID == 30004662) || (tempID == 30004663) || (tempID == 

				30004664) || (tempID == 30004665) || (tempID == 30004666) || (tempID == 30004667) || (tempID == 30004668) || 

				(tempID == 30004669) || (tempID == 30004670) || (tempID == 30004671) || (tempID == 30004672) || (tempID == 

				30004673) || (tempID == 30004674) || (tempID == 30004675) || (tempID == 30004676) || (tempID == 30004677) || 

				(tempID == 30004678) || (tempID == 30004679) || (tempID == 30004680) || (tempID == 30004681) || (tempID == 

				30004682) || (tempID == 30004683) || (tempID == 30004684) || (tempID == 30004685) || (tempID == 30004686) || 

				(tempID == 30004687) || (tempID == 30004688) || (tempID == 30004689) || (tempID == 30004690) || (tempID == 

				30004691) || (tempID == 30004692) || (tempID == 30004693) || (tempID == 30004694) || (tempID == 30004695) || 

				(tempID == 30004696) || (tempID == 30004697) || (tempID == 30004698) || (tempID == 30004699) || (tempID == 

				30004700) || (tempID == 30004701) || (tempID == 30004702) || (tempID == 30004703) || (tempID == 30004704) || 

				(tempID == 30004705) || (tempID == 30004706))writer.write(tempString + "\n"); else if((tempID == 30004706) || 

				(tempID == 30004707) || (tempID == 30004708) || (tempID == 30004709) || (tempID == 30004710) || (tempID == 

				30004711) || (tempID == 30004712) || (tempID == 30004713) || (tempID == 30004714) || (tempID == 30004715) || 

				(tempID == 30004716) || (tempID == 30004717) || (tempID == 30004718) || (tempID == 30004719) || (tempID == 

				30004720) || (tempID == 30004721) || (tempID == 30004722) || (tempID == 30004723) || (tempID == 30004724) || 

				(tempID == 30004725) || (tempID == 30004726) || (tempID == 30004727) || (tempID == 30004728) || (tempID == 

				30004729) || (tempID == 30004730) || (tempID == 30004731) || (tempID == 30004732) || (tempID == 30004733) || 

				(tempID == 30004734) || (tempID == 30004735) || (tempID == 30004736) || (tempID == 30004737) || (tempID == 

				30004738) || (tempID == 30004739) || (tempID == 30004740) || (tempID == 30004741) || (tempID == 30004742) || 

				(tempID == 30004743) || (tempID == 30004744) || (tempID == 30004745) || (tempID == 30004746) || (tempID == 

				30004747) || (tempID == 30004748) || (tempID == 30004749) || (tempID == 30004750) || (tempID == 30004751) || 

				(tempID == 30004752) || (tempID == 30004753) || (tempID == 30004754) || (tempID == 30004755) || (tempID == 

				30004756) || (tempID == 30004757) || (tempID == 30004758) || (tempID == 30004759) || (tempID == 30004760) || 

				(tempID == 30004761) || (tempID == 30004762) || (tempID == 30004763) || (tempID == 30004764) || (tempID == 

				30004765) || (tempID == 30004766) || (tempID == 30004767) || (tempID == 30004768) || (tempID == 30004769) || 

				(tempID == 30004770) || (tempID == 30004771))writer.write(tempString + "\n"); else if((tempID == 30004771) || 

				(tempID == 30004772) || (tempID == 30004773) || (tempID == 30004774) || (tempID == 30004775) || (tempID == 

				30004776) || (tempID == 30004777) || (tempID == 30004778) || (tempID == 30004779) || (tempID == 30004780) || 

				(tempID == 30004781) || (tempID == 30004782) || (tempID == 30004783) || (tempID == 30004784) || (tempID == 

				30004785) || (tempID == 30004786) || (tempID == 30004787) || (tempID == 30004788) || (tempID == 30004789) || 

				(tempID == 30004790) || (tempID == 30004791) || (tempID == 30004792) || (tempID == 30004793) || (tempID == 

				30004794) || (tempID == 30004795) || (tempID == 30004796) || (tempID == 30004797) || (tempID == 30004798) || 

				(tempID == 30004799) || (tempID == 30004800) || (tempID == 30004801) || (tempID == 30004802) || (tempID == 

				30004803) || (tempID == 30004804) || (tempID == 30004805) || (tempID == 30004806) || (tempID == 30004807) || 

				(tempID == 30004808) || (tempID == 30004809) || (tempID == 30004810) || (tempID == 30004811) || (tempID == 

				30004812) || (tempID == 30004813) || (tempID == 30004814) || (tempID == 30004815) || (tempID == 30004816) || 

				(tempID == 30004817) || (tempID == 30004818) || (tempID == 30004819) || (tempID == 30004820) || (tempID == 

				30004821) || (tempID == 30004822) || (tempID == 30004823) || (tempID == 30004824) || (tempID == 30004825) || 

				(tempID == 30004826) || (tempID == 30004827) || (tempID == 30004828) || (tempID == 30004829) || (tempID == 

				30004830) || (tempID == 30004831) || (tempID == 30004832) || (tempID == 30004833) || (tempID == 30004834) || 

				(tempID == 30004835) || (tempID == 30004836))writer.write(tempString + "\n"); else if((tempID == 30004836) || 

				(tempID == 30004837) || (tempID == 30004838) || (tempID == 30004839) || (tempID == 30004840) || (tempID == 

				30004841) || (tempID == 30004842) || (tempID == 30004843) || (tempID == 30004844) || (tempID == 30004845) || 

				(tempID == 30004846) || (tempID == 30004847) || (tempID == 30004848) || (tempID == 30004849) || (tempID == 

				30004850) || (tempID == 30004851) || (tempID == 30004852) || (tempID == 30004853) || (tempID == 30004854) || 

				(tempID == 30004855) || (tempID == 30004856) || (tempID == 30004857) || (tempID == 30004858) || (tempID == 

				30004859) || (tempID == 30004860) || (tempID == 30004861) || (tempID == 30004862) || (tempID == 30004863) || 

				(tempID == 30004864) || (tempID == 30004865) || (tempID == 30004866) || (tempID == 30004867) || (tempID == 

				30004868) || (tempID == 30004869) || (tempID == 30004870) || (tempID == 30004871) || (tempID == 30004872) || 

				(tempID == 30004873) || (tempID == 30004874) || (tempID == 30004875) || (tempID == 30004876) || (tempID == 

				30004877) || (tempID == 30004878) || (tempID == 30004879) || (tempID == 30004880) || (tempID == 30004881) || 

				(tempID == 30004882) || (tempID == 30004883) || (tempID == 30004884) || (tempID == 30004885) || (tempID == 

				30004886) || (tempID == 30004887) || (tempID == 30004888) || (tempID == 30004889) || (tempID == 30004890) || 

				(tempID == 30004891) || (tempID == 30004892) || (tempID == 30004893) || (tempID == 30004894) || (tempID == 

				30004895) || (tempID == 30004896) || (tempID == 30004897) || (tempID == 30004898) || (tempID == 30004899) || 

				(tempID == 30004900) || (tempID == 30004901) || (tempID == 30004902) || (tempID == 

				30004903))writer.write(tempString + "\n"); else if((tempID == 30004903) || (tempID == 30004904) || (tempID == 

				30004905) || (tempID == 30004906) || (tempID == 30004907) || (tempID == 30004908) || (tempID == 30004909) || 

				(tempID == 30004910) || (tempID == 30004911) || (tempID == 30004912) || (tempID == 30004913) || (tempID == 

				30004914) || (tempID == 30004915) || (tempID == 30004916) || (tempID == 30004917) || (tempID == 30004918) || 

				(tempID == 30004919) || (tempID == 30004920) || (tempID == 30004921) || (tempID == 30004922) || (tempID == 

				30004923) || (tempID == 30004924) || (tempID == 30004925) || (tempID == 30004926) || (tempID == 30004927) || 

				(tempID == 30004929) || (tempID == 30004930) || (tempID == 30004931) || (tempID == 30004932) || (tempID == 

				30004933) || (tempID == 30004934) || (tempID == 30004935) || (tempID == 30004936) || (tempID == 30004937) || 

				(tempID == 30004938) || (tempID == 30004939) || (tempID == 30004940) || (tempID == 30004941) || (tempID == 

				30004942) || (tempID == 30004943) || (tempID == 30004944) || (tempID == 30004945) || (tempID == 30004946) || 

				(tempID == 30004947) || (tempID == 30004948) || (tempID == 30004949) || (tempID == 30004950) || (tempID == 

				30004951) || (tempID == 30004952) || (tempID == 30004953) || (tempID == 30004954) || (tempID == 30004955) || 

				(tempID == 30004956) || (tempID == 30004957) || (tempID == 30004958) || (tempID == 30004959) || (tempID == 

				30004960) || (tempID == 30004961) || (tempID == 30004962) || (tempID == 30004963) || (tempID == 30004964) || 

				(tempID == 30004965) || (tempID == 30004966) || (tempID == 30004979) || (tempID == 30004980) || (tempID == 

				30004982) || (tempID == 30004984) || (tempID == 30004985) || (tempID == 30004991) || (tempID == 30004999) || 

				(tempID == 30005000) || (tempID == 30005008))writer.write(tempString + "\n"); else if((tempID == 30005008) || 

				(tempID == 30005014) || (tempID == 30005022) || (tempID == 30005032) || (tempID == 30005033) || (tempID == 

				30005062) || (tempID == 30005063) || (tempID == 30005064) || (tempID == 30005065) || (tempID == 30005066) || 

				(tempID == 30005067) || (tempID == 30005068) || (tempID == 30005073) || (tempID == 30005074) || (tempID == 

				30005086) || (tempID == 30005088) || (tempID == 30005089) || (tempID == 30005090) || (tempID == 30005091) || 

				(tempID == 30005092) || (tempID == 30005093) || (tempID == 30005094) || (tempID == 30005095) || (tempID == 

				30005096) || (tempID == 30005097) || (tempID == 30005098) || (tempID == 30005099) || (tempID == 30005100) || 

				(tempID == 30005101) || (tempID == 30005102) || (tempID == 30005103) || (tempID == 30005104) || (tempID == 

				30005105) || (tempID == 30005106) || (tempID == 30005107) || (tempID == 30005108) || (tempID == 30005109) || 

				(tempID == 30005110) || (tempID == 30005111) || (tempID == 30005112) || (tempID == 30005113) || (tempID == 

				30005114) || (tempID == 30005115) || (tempID == 30005116) || (tempID == 30005117) || (tempID == 30005118) || 

				(tempID == 30005119) || (tempID == 30005120) || (tempID == 30005121) || (tempID == 30005122) || (tempID == 

				30005123) || (tempID == 30005124) || (tempID == 30005125) || (tempID == 30005126) || (tempID == 30005127) || 

				(tempID == 30005128) || (tempID == 30005129) || (tempID == 30005130) || (tempID == 30005131) || (tempID == 

				30005132) || (tempID == 30005133) || (tempID == 30005134) || (tempID == 30005135) || (tempID == 30005136) || 

				(tempID == 30005137) || (tempID == 30005138) || (tempID == 30005139) || (tempID == 30005140) || (tempID == 

				30005141) || (tempID == 30005142) || (tempID == 30005143))writer.write(tempString + "\n"); else if((tempID == 

				30005143) || (tempID == 30005144) || (tempID == 30005145) || (tempID == 30005146) || (tempID == 30005147) || 

				(tempID == 30005148) || (tempID == 30005149) || (tempID == 30005150) || (tempID == 30005151) || (tempID == 

				30005152) || (tempID == 30005153) || (tempID == 30005154) || (tempID == 30005155) || (tempID == 30005156) || 

				(tempID == 30005157) || (tempID == 30005158) || (tempID == 30005159) || (tempID == 30005160) || (tempID == 

				30005161) || (tempID == 30005162) || (tempID == 30005163) || (tempID == 30005164) || (tempID == 30005165) || 

				(tempID == 30005166) || (tempID == 30005167) || (tempID == 30005168) || (tempID == 30005169) || (tempID == 

				30005170) || (tempID == 30005171) || (tempID == 30005172) || (tempID == 30005173) || (tempID == 30005174) || 

				(tempID == 30005175) || (tempID == 30005176) || (tempID == 30005177) || (tempID == 30005178) || (tempID == 

				30005179) || (tempID == 30005180) || (tempID == 30005181) || (tempID == 30005182) || (tempID == 30005183) || 

				(tempID == 30005184) || (tempID == 30005185) || (tempID == 30005186) || (tempID == 30005187) || (tempID == 

				30005188) || (tempID == 30005189) || (tempID == 30005190) || (tempID == 30005191) || (tempID == 30005234) || 

				(tempID == 30005236) || (tempID == 30005237) || (tempID == 30005238) || (tempID == 30005239) || (tempID == 

				30005240) || (tempID == 30005241) || (tempID == 30005242) || (tempID == 30005255) || (tempID == 30005257) || 

				(tempID == 30005258) || (tempID == 30005259) || (tempID == 30005261) || (tempID == 30005262) || (tempID == 

				30005263) || (tempID == 30005264) || (tempID == 30005265) || (tempID == 30005266) || (tempID == 30005268) || 

				(tempID == 30005270) || (tempID == 30005271) || (tempID == 30005272) || (tempID == 30005273) || (tempID == 

				30005274) || (tempID == 30005275) || (tempID == 30005276))writer.write(tempString + "\n"); else if((tempID == 

				30005276) || (tempID == 30005277) || (tempID == 30005278) || (tempID == 30005281) || (tempID == 30005282) || 

				(tempID == 30005283) || (tempID == 30005284) || (tempID == 30005285) || (tempID == 30005287) || (tempID == 

				30005295) || (tempID == 30005296) || (tempID == 30005298) || (tempID == 30005299) || (tempID == 30005300) || 

				(tempID == 30005321))writer.write(tempString + "\n");
		}
		writer.close();
	}
	
	// SYSTEMSTOKEEP.txt to systemsConstructor.txt
	private void systemsConstructor() throws Exception{
		writer.write("itemID constellationID itemName\n");
		while(scanner.hasNext()){
			tempString = scanner.nextLine();
			tempID = Integer.parseInt(tempString.substring(0, 8));
			constellationID = Integer.parseInt(tempString.substring(18, 26));
			tempString = tempString.substring(tempString.indexOf('\'') + 1, tempString.indexOf('\'', tempString.indexOf('\'') + 1));
			writer.write(tempID + " " + constellationID + " " + tempString + "\n");
		}
		writer.close();
	}
	
	// regions.txt to regionsConstructor.txt
	private void regionsConstructor() throws Exception{
		scanner.nextLine();
		scanner.nextLine();
		writer.write("itemID itemName\n");
		while(scanner.hasNext()){
			tempString = scanner.nextLine();
			tempID = Integer.parseInt(tempString.substring(0, 8));
			tempString = tempString.substring(tempString.indexOf('\'') + 1, tempString.indexOf('\'', tempString.indexOf('\'') + 1));
			writer.write(tempID + " " + tempString + "\n");
		}
		writer.close();
	}
	
	// constellations.txt to constellationsConstructor.txt
	private void constellationsConstructor() throws Exception{
		scanner.nextLine();
		scanner.nextLine();
		writer.write("itemID regionID itemName\n");
		while(scanner.hasNext()){
			tempString = scanner.nextLine();
			tempID = Integer.parseInt(tempString.substring(0, 8));
			regionID = Integer.parseInt(tempString.substring(23, 31));
			tempString = tempString.substring(tempString.indexOf('\'') + 1, tempString.indexOf('\'', tempString.indexOf('\'') + 1));
			writer.write(tempID + " " + regionID + " " + tempString + "\n");
		}
		writer.close();
	}	
	
	// MOONSTOKEEP.txt to moonsConstructor.txt
	private void moonsConstructor() throws Exception{
		writer.write("itemID systemID itemName\n");
		while(scanner.hasNext()){
			tempString = scanner.nextLine();
			tempID = Integer.parseInt(tempString.substring(0, 8));
			systemID = Integer.parseInt(tempString.substring(14, 22));
			tempString = tempString.substring(tempString.indexOf('\'') + 1, tempString.indexOf('\'', tempString.indexOf('\'') + 1));
			writer.write(tempID + " " + systemID + " " + tempString + "\n");
		}
		writer.close();
	}
	
	public static void main(String[] args) {
		try{
			converter conv = new converter();
			conv.scanner = new Scanner(new File("C:/constellationsConstructor.txt"));
		//	conv.writer = new FileWriter(new File("C:/constellationsConstructor2.txt"));			
			conv.constellationsToKeep();
		}catch(Exception e){
			System.out.println("Not Found.");
			System.exit(0);
		}
			/**
			int oldID = 0;
			writer.write("if(");			
			
			
			while(scanner.hasNextLine()){				
				String tempString = scanner.nextLine();		
			//	int tempID = Integer.parseInt(tempString.substring(0, 8));
			//	int regionID = Integer.parseInt(tempString.substring(18, 26));
				//writer.write("region[" + (regionID - 10000000) + "].insert(constellation[" + (tempID - 20000000) + "]);\n");
				/**
				writer.write("solarSystem[" + (tempID - 30000000) + "] = new SolarSystem(" + tempID + ",\"");
				tempString = tempString.substring(tempString.indexOf('\'')+1, tempString.indexOf('\'', tempString.indexOf('\'') +1));
				writer.write(tempString + "\");\n");
				*/
				/**
				int systemID = Integer.parseInt(tempString.substring(14, 22));
				String security = tempString.substring(tempString.indexOf('.') +1, tempString.indexOf('.') +3);
				
				
				if(oldID != systemID){					
					oldID = systemID;
					writer.write("tempString.constains(\"" + systemID + "\") || ");
				}
				*/
				
			/**
		//	writer.write(")writer.write(tempString);");
			writer.close();
			*/
		
	}

}
