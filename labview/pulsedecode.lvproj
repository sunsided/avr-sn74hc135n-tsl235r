<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="ASCII Processing" Type="Folder">
			<Item Name="CreateASCIIQueue.vi" Type="VI" URL="../CreateASCIIQueue.vi"/>
			<Item Name="DestroyASCIIQueue.vi" Type="VI" URL="../DestroyASCIIQueue.vi"/>
			<Item Name="SensorASCIIProcessor.vi" Type="VI" URL="../SensorASCIIProcessor.vi"/>
			<Item Name="SensorDataType.ctl" Type="VI" URL="../SensorDataType.ctl"/>
		</Item>
		<Item Name="Processing" Type="Folder">
			<Item Name="AngleDecode.vi" Type="VI" URL="../AngleDecode.vi"/>
			<Item Name="Ausgangswinkel.vi" Type="VI" URL="../Ausgangswinkel.vi"/>
			<Item Name="PeakDetect.vi" Type="VI" URL="../PeakDetect.vi"/>
		</Item>
		<Item Name="Serial In" Type="Folder">
			<Item Name="SensorSerialReceiver.vi" Type="VI" URL="../SensorSerialReceiver.vi"/>
		</Item>
		<Item Name="Serial Out" Type="Folder">
			<Item Name="SerialOut.vi" Type="VI" URL="../SerialOut.vi"/>
		</Item>
		<Item Name="Shutdown" Type="Folder">
			<Item Name="DestroyShutdownNotifier.vi" Type="VI" URL="../DestroyShutdownNotifier.vi"/>
			<Item Name="DetectShutdownNotification.vi" Type="VI" URL="../DetectShutdownNotification.vi"/>
			<Item Name="PrepareShutdownNotifier.vi" Type="VI" URL="../PrepareShutdownNotifier.vi"/>
		</Item>
		<Item Name="Simulation" Type="Folder">
			<Item Name="ArrayToProtocol.vi" Type="VI" URL="../ArrayToProtocol.vi"/>
			<Item Name="SimulatedToArray.vi" Type="VI" URL="../SimulatedToArray.vi"/>
			<Item Name="TSL235R.vi" Type="VI" URL="../TSL235R.vi"/>
		</Item>
		<Item Name="SensorArray.vi" Type="VI" URL="../SensorArray.vi"/>
		<Item Name="TopLevel.vi" Type="VI" URL="../TopLevel.vi"/>
		<Item Name="TSL235R-Test.vi" Type="VI" URL="../TSL235R-Test.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Check for Equality.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/WDTOps.llb/Check for Equality.vi"/>
				<Item Name="DU64_U32SubtractWithBorrow.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/TSOps.llb/DU64_U32SubtractWithBorrow.vi"/>
				<Item Name="Dynamic To Waveform Array.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/transition.llb/Dynamic To Waveform Array.vi"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="ex_GetAllExpressAttribs.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/transition.llb/ex_GetAllExpressAttribs.vi"/>
				<Item Name="ex_Modify Signal Name.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_Modify Signal Name.vi"/>
				<Item Name="ex_Modify Signals Names.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_Modify Signals Names.vi"/>
				<Item Name="ex_SmoothingDesign.vi" Type="VI" URL="/&lt;vilib&gt;/express/express analysis/FilterBlock.llb/ex_SmoothingDesign.vi"/>
				<Item Name="ex_WaveformAttribs.ctl" Type="VI" URL="/&lt;vilib&gt;/express/express shared/transition.llb/ex_WaveformAttribs.ctl"/>
				<Item Name="Express Waveform Components.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/transition.llb/Express Waveform Components.vi"/>
				<Item Name="I128 Timestamp.ctl" Type="VI" URL="/&lt;vilib&gt;/Waveform/TSOps.llb/I128 Timestamp.ctl"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_MABase.lvlib" Type="Library" URL="/&lt;vilib&gt;/measure/NI_MABase.lvlib"/>
				<Item Name="NI_MAPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/measure/NI_MAPro.lvlib"/>
				<Item Name="NI_PtbyPt.lvlib" Type="Library" URL="/&lt;vilib&gt;/ptbypt/NI_PtbyPt.lvlib"/>
				<Item Name="subFilter.vi" Type="VI" URL="/&lt;vilib&gt;/express/express analysis/FilterBlock.llb/subFilter.vi"/>
				<Item Name="Timestamp Subtract.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/TSOps.llb/Timestamp Subtract.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="PeakInterpolate.vi" Type="VI" URL="../PeakInterpolate.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
