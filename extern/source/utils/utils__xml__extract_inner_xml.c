#include <stdio.h>
#include <stddef.h>


int utils__xml__extract_inner_xml (const char* xml_document, size_t xml_document_len,  const char* name, size_t name_len, char *value, size_t value_size, size_t* value_len)
{
	size_t i;
	size_t j;
	size_t k;
	int done;
	int state;


	if (xml_document == NULL)
	{
		return -100;
	}

	if (xml_document_len == 0)
	{
		return -200;
	}

	if (name == NULL)
	{
		return -300;
	}

	if (name_len == 0)
	{
		return -400;
	}

	if (value == NULL)
	{
		return -500;
	}

	if (value_size == 0)
	{
		return -600;
	}

	if (value_len == NULL)
	{
		return -700;
	}

	
	i = 0;
	j = 0;
	k = 0;
	done = 0;
	state = 0;
	do
	{
		switch (state)
		{
		    case 0:
			if (xml_document[i] == '<')
			{
				state = 1;
			}
		    break;

			case 1:
				if (xml_document[i] == name[j])
				{
					j++;
					if (j >= name_len)
					{
						state = 2;
					}
				}
				else
				{
					j = 0;
					state = 0;
				}
			break;

			case 2:
				if (xml_document[i] == ' ')
				{
					state = 3;
				}
				else
				{
					j = 0;
					state = 0;
				}
				break;

			case 3:
				if (xml_document[i] == '>')
				{
					k = 0;
					state = 4;
				}
			break;

			case 4:
				if (xml_document[i] == '<')
				{
					/* 
					 * if (k + 1 > value_size) allows us to safely terminate value 
					 */
					value[k] = '\0';
					j = 0;
					state = 5;
				}
				else
				{
					value[k] = xml_document[i];
					k++;
					if (k + 1 > value_size)
					{
						return -2000;
					}
				}
			break;

			case 5:
				if (xml_document[i] == '/')
				{
					state = 6;
				}
				else
				{
					return -3000;
				}
				break;


			case 6:
				if (xml_document[i] == name[j])
				{
					j++;
					if (j >= name_len)
					{
						state = 7;
					}
				}
				else
				{
					return -4000;
				}
				break;

			case 7:
				if (xml_document[i] == '>')
				{
					done = 1;
				}
				else
				{
					return -5000;
				}
				break;

			default:
				return -6000;
				break;

		}

		if (done == 0)
		{
			i++;
			if (i >= xml_document_len)
			{
				done = 2;
			}
		}

	}
	while (done == 0);


	if (done != 1)
	{
		return -10000;
	}

	*value_len = k;

	return 0;
}



#if 0

extern int utils__xml__extract_inner_xml(const char* xml_document, size_t xml_document_len, const char* name, size_t name_len, char* value, size_t value_size, size_t* value_len);

static const char* xml =
"HTTP/1.0 200 OK\n"
"Content-Length: 10530\n"
"Content-Type: text/xml\n"
"\n"
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<?xml-stylesheet type=\"text/xsl\" href=\"/styles/Streams.xsl\"?>\n"
"<MTConnectStreams xmlns:m=\"urn:mtconnect.org:MTConnectStreams:1.3\" xmlns=\"urn:mtconnect.org:MTConnectStreams:1.3\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:e=\"urn:okuma.com:OkumaStreams:1.3\" xsi:schemaLocation=\"urn:okuma.com:OkumaStreams:1.3 /schemas/OkumaStreams_1.3.xsd\">\n"
"  <Header creationTime=\"2022-01-17T14:44:45Z\" sender=\"OKUMA-P234077\" instanceId=\"1642402168\" version=\"1.3.0.15\" bufferSize=\"131072\" nextSequence=\"322765\" firstSequence=\"191693\" lastSequence=\"322764\"/>\n"
"  <Streams>\n"
"    <DeviceStream name=\"OKUMA.Lathe\" uuid=\"OKUMA.Lathe.123456\">\n"
"      <ComponentStream component=\"Rotary\" name=\"C\" componentId=\"Lc1\">\n"
"        <Samples>\n"
"          <e:SurfaceSpeed dataItemId=\"LS1SurfaceSpeed\" timestamp=\"2022-01-17T14:44:45.200Z\" name=\"S1SurfaceSpeed\" sequence=\"322749\">1250</e:SurfaceSpeed>\n"
"          <RotaryVelocity dataItemId=\"LS1cmd\" timestamp=\"2022-01-17T14:44:30.719Z\" name=\"S1cmd\" sequence=\"322576\" subType=\"PROGRAMMED\">2000</RotaryVelocity>\n"
"          <Load dataItemId=\"LS1load\" timestamp=\"2022-01-17T14:44:43.825Z\" name=\"S1load\" sequence=\"322734\">12</Load>\n"
"          <RotaryVelocity dataItemId=\"LS1speed\" timestamp=\"2022-01-17T14:44:45.196Z\" name=\"S1speed\" sequence=\"322748\" subType=\"ACTUAL\">2002</RotaryVelocity>\n"
"        </Samples>\n"
"        <Events>\n"
"          <ChuckState dataItemId=\"LS1ChuckState\" timestamp=\"2022-01-17T14:44:28.844Z\" name=\"S1ChuckState\" sequence=\"322550\">CLOSED</ChuckState>\n"
"          <RotaryMode dataItemId=\"LS1Mode\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"S1Mode\" sequence=\"59\">SPINDLE</RotaryMode>\n"
"          <RotaryVelocityOverride dataItemId=\"LS1ovr\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"S1ovr\" sequence=\"58\" subType=\"PROGRAMMED\">100</RotaryVelocityOverride>\n"
"        </Events>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Rotary\" name=\"C3\" componentId=\"Lc3\">\n"
"        <Samples>\n"
"          <Angle dataItemId=\"LC3actm\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"C3actm\" sequence=\"82\" subType=\"ACTUAL\">300</Angle>\n"
"          <Angle dataItemId=\"LC3actw\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"C3actw\" sequence=\"83\" subType=\"ACTUAL\">300</Angle>\n"
"          <Load dataItemId=\"LC3load\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"C3load\" sequence=\"84\">0</Load>\n"
"        </Samples>\n"
"        <Events>\n"
"          <RotaryMode dataItemId=\"LC3Mode\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"C3Mode\" sequence=\"61\">INDEX</RotaryMode>\n"
"        </Events>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Rotary\" name=\"C6\" componentId=\"Lc6\">\n"
"        <Samples>\n"
"          <RotaryVelocity dataItemId=\"LS6cmd\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"S6cmd\" sequence=\"86\" subType=\"PROGRAMMED\">0</RotaryVelocity>\n"
"          <Load dataItemId=\"LS6load\" timestamp=\"2022-01-17T14:44:21.780Z\" name=\"S6load\" sequence=\"322463\">3</Load>\n"
"          <RotaryVelocity dataItemId=\"LS6speed\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"S6speed\" sequence=\"85\" subType=\"ACTUAL\">0</RotaryVelocity>\n"
"        </Samples>\n"
"        <Events>\n"
"          <RotaryMode dataItemId=\"LS6Mode\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"S6Mode\" sequence=\"63\">SPINDLE</RotaryMode>\n"
"          <RotaryVelocityOverride dataItemId=\"LS6ovr\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"S6ovr\" sequence=\"62\" subType=\"PROGRAMMED\">100</RotaryVelocityOverride>\n"
"        </Events>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Controller\" name=\"Controller\" componentId=\"Lct1\">\n"
"        <Samples>\n"
"          <AccumulatedTime dataItemId=\"LpCuttingTime\" timestamp=\"2022-01-17T14:44:45.184Z\" name=\"pCuttingTime\" sequence=\"322761\" subType=\"x:CUTTING_TIME\">11445</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpOperatingTime\" timestamp=\"2022-01-17T14:44:45.162Z\" name=\"pOperatingTime\" sequence=\"322759\" subType=\"x:OPERATING_TIME\">27570</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpRunningTime\" timestamp=\"2022-01-17T14:44:45.173Z\" name=\"pRunningTime\" sequence=\"322760\" subType=\"x:RUNNING_TIME\">28485</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpSpindleRunTime\" timestamp=\"2022-01-17T14:44:45.196Z\" name=\"pSpindleRunTime\" sequence=\"322762\" subType=\"x:SPINDLE_RUN_TIME\">22811</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpTotalCuttingTime\" timestamp=\"2022-01-17T14:44:45.132Z\" name=\"pTotalCuttingTime\" sequence=\"322757\" subType=\"x:TOTAL_CUTTING_TIME\">1096434</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpTotalOperatingTime\" timestamp=\"2022-01-17T14:44:45.108Z\" name=\"pTotalOperatingTime\" sequence=\"322755\" subType=\"x:TOTAL_OPERATING_TIME\">1850727</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpTotalRunningTime\" timestamp=\"2022-01-17T14:44:45.120Z\" name=\"pTotalRunningTime\" sequence=\"322756\" subType=\"x:TOTAL_RUNNING_TIME\">3117720</AccumulatedTime>\n"
"          <AccumulatedTime dataItemId=\"LpTotalSpindleRunTime\" timestamp=\"2022-01-17T14:44:45.151Z\" name=\"pTotalSpindleRunTime\" sequence=\"322758\" subType=\"x:TOTAL_SPINDLE_RUN_TIME\">1640620</AccumulatedTime>\n"
"        </Samples>\n"
"        <Events>\n"
"          <EmergencyStop dataItemId=\"Lestop\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"estop\" sequence=\"64\">ARMED</EmergencyStop>\n"
"          <e:Variables dataItemId=\"Lp1CommonVariable\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"p1CommonVariable\" sequence=\"70\" subType=\"x:COMMON\">1:18</e:Variables>\n"
"          <e:Macman dataItemId=\"Lp1MacManPanelHistory\" timestamp=\"2022-01-17T06:54:23.871Z\" name=\"p1MacManPanelHistory\" sequence=\"810\" subType=\"x:PANEL_HISTORY\">2022/01/17 07:54:23 Run mode Change:AUTO</e:Macman>\n"
"          <e:OutputSignal dataItemId=\"Lp1MachineOperationPanelOutputDryRun\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"p1MachineOperationPanelOutputDryRun\" sequence=\"72\" subType=\"x:DRY_RUN\">OFF</e:OutputSignal>\n"
"          <e:OutputSignal dataItemId=\"Lp1MachineOperationPanelOutputMachineLock\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"p1MachineOperationPanelOutputMachineLock\" sequence=\"73\" subType=\"x:MACHINE_LOCK\">OFF</e:OutputSignal>\n"
"          <PathFeedrateOverride dataItemId=\"LpFovr\" timestamp=\"2022-01-17T06:52:45.910Z\" name=\"pFovr\" sequence=\"579\" subType=\"PROGRAMMED\">100</PathFeedrateOverride>\n"
"          <Execution dataItemId=\"Lpexecution\" timestamp=\"2022-01-17T14:20:24.078Z\" name=\"pexecution\" sequence=\"305972\">ACTIVE</Execution>\n"
"          <ControllerMode dataItemId=\"Lpmode\" timestamp=\"2022-01-17T06:54:23.519Z\" name=\"pmode\" sequence=\"806\">AUTOMATIC</ControllerMode>\n"
"          <PartCount dataItemId=\"Lppartcount\" timestamp=\"2022-01-17T14:44:20.015Z\" name=\"ppartcount\" sequence=\"322439\">510</PartCount>\n"
"          <Program dataItemId=\"Lpprogram\" timestamp=\"2022-01-17T06:51:58.538Z\" name=\"pprogram\" sequence=\"223\">E0047.MIN</Program>\n"
"        </Events>\n"
"        <Condition>\n"
"          <Normal dataItemId=\"Lsystem\" timestamp=\"2022-01-17T08:31:02.181Z\" name=\"system\" sequence=\"61351\" type=\"SYSTEM\"/>\n"
"        </Condition>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Path\" name=\"path\" componentId=\"Lp1\">\n"
"        <Samples>\n"
"          <PathFeedrate dataItemId=\"Lp1Fact\" timestamp=\"2022-01-17T14:44:29.410Z\" name=\"p1Fact\" sequence=\"322569\" subType=\"ACTUAL\">UNAVAILABLE</PathFeedrate>\n"
"          <PathFeedrate dataItemId=\"Lp1Fcmd\" timestamp=\"2022-01-17T14:44:29.410Z\" name=\"p1Fcmd\" sequence=\"322570\" subType=\"PROGRAMMED\">UNAVAILABLE</PathFeedrate>\n"
"          <PathPosition dataItemId=\"Lp1LPathPos\" timestamp=\"2022-01-17T14:44:45.220Z\" name=\"p1LPathPos\" sequence=\"322763\">22.4 0 10</PathPosition>\n"
"        </Samples>\n"
"        <Events>\n"
"          <ToolNumber dataItemId=\"Lp1CurrentTool\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"p1CurrentTool\" sequence=\"76\"/>\n"
"          <ToolAssetId dataItemId=\"Lp1ToolAssetId\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"p1ToolAssetId\" sequence=\"77\"/>\n"
"          <Block dataItemId=\"Lp1block\" timestamp=\"2022-01-17T14:44:45.528Z\" name=\"p1block\" sequence=\"322764\">G0 X800 M9</Block>\n"
"          <Line dataItemId=\"Lp1line\" timestamp=\"2022-01-17T14:44:39.507Z\" name=\"p1line\" sequence=\"322683\">A5</Line>\n"
"        </Events>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Linear\" name=\"X\" componentId=\"Lx1\">\n"
"        <Samples>\n"
"          <Position dataItemId=\"LX1actm\" timestamp=\"2022-01-17T14:44:45.217Z\" name=\"X1actm\" sequence=\"322750\" subType=\"ACTUAL\">32851.87</Position>\n"
"          <Position dataItemId=\"LX1actw\" timestamp=\"2022-01-17T14:44:45.219Z\" name=\"X1actw\" sequence=\"322751\" subType=\"ACTUAL\">22.4</Position>\n"
"          <Load dataItemId=\"LX1load\" timestamp=\"2022-01-17T14:44:42.595Z\" name=\"X1load\" sequence=\"322720\">48</Load>\n"
"        </Samples>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Linear\" name=\"Z\" componentId=\"Lz1\">\n"
"        <Samples>\n"
"          <Position dataItemId=\"LZ1actm\" timestamp=\"2022-01-17T14:44:45.219Z\" name=\"Z1actm\" sequence=\"322752\" subType=\"ACTUAL\">53293.229</Position>\n"
"          <Position dataItemId=\"LZ1actw\" timestamp=\"2022-01-17T14:44:45.219Z\" name=\"Z1actw\" sequence=\"322753\" subType=\"ACTUAL\">10</Position>\n"
"          <Load dataItemId=\"LZ1load\" timestamp=\"2022-01-17T14:44:45.219Z\" name=\"Z1load\" sequence=\"322754\">59</Load>\n"
"        </Samples>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Linear\" name=\"Z4\" componentId=\"Lz4\">\n"
"        <Samples>\n"
"          <Position dataItemId=\"LZ4actm\" timestamp=\"2022-01-17T14:44:19.284Z\" name=\"Z4actm\" sequence=\"322429\" subType=\"ACTUAL\">98861.7</Position>\n"
"          <Position dataItemId=\"LZ4actw\" timestamp=\"2022-01-17T14:44:20.533Z\" name=\"Z4actw\" sequence=\"322452\" subType=\"ACTUAL\">667.8</Position>\n"
"          <Load dataItemId=\"LZ4load\" timestamp=\"2022-01-17T14:44:28.161Z\" name=\"Z4load\" sequence=\"322541\">2</Load>\n"
"        </Samples>\n"
"      </ComponentStream>\n"
"      <ComponentStream component=\"Device\" name=\"OKUMA.Lathe\" componentId=\"OKUMA.Lathe\">\n"
"        <Events>\n"
"          <Availability dataItemId=\"Lavail\" timestamp=\"2022-01-17T06:51:20.9256896Z\" name=\"avail\" sequence=\"56\">AVAILABLE</Availability>\n"
"          <FunctionalMode dataItemId=\"Lfmode\" timestamp=\"2022-01-17T14:34:35.845Z\" name=\"fmode\" sequence=\"315941\">PRODUCTION</FunctionalMode>\n"
"          <AssetChanged dataItemId=\"OKUMA.Lathe_asset_chg\" timestamp=\"2022-01-17T06:49:28.047643Z\" sequence=\"54\" assetType=\"\">UNAVAILABLE</AssetChanged>\n"
"          <AssetRemoved dataItemId=\"OKUMA.Lathe_asset_rem\" timestamp=\"2022-01-17T06:49:28.047643Z\" sequence=\"55\" assetType=\"\">UNAVAILABLE</AssetRemoved>\n"
"        </Events>\n"
"      </ComponentStream>\n"
"    </DeviceStream>\n"
"  </Streams>\n"
"</MTConnectStreams>";


#include <string.h>

int test(void)
{
	int rc;
	size_t xml_document_len;
	char value[256];
	size_t value_len;

	xml_document_len = strlen(xml);
	
	rc = utils__xml__extract_inner_xml(xml, xml_document_len, "PartCount", 9, value, sizeof(value), &value_len);

	return rc;
}

#endif