﻿<?xml version='1.0' encoding='UTF-8'?>
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
			<Item Name="PeakDetect.vi" Type="VI" URL="../PeakDetect.vi"/>
		</Item>
		<Item Name="Serial In" Type="Folder">
			<Item Name="SensorSerialReceiver.vi" Type="VI" URL="../SensorSerialReceiver.vi"/>
		</Item>
		<Item Name="Shutdown" Type="Folder">
			<Item Name="DestroyShutdownNotifier.vi" Type="VI" URL="../DestroyShutdownNotifier.vi"/>
			<Item Name="DetectShutdownNotification.vi" Type="VI" URL="../DetectShutdownNotification.vi"/>
			<Item Name="PrepareShutdownNotifier.vi" Type="VI" URL="../PrepareShutdownNotifier.vi"/>
		</Item>
		<Item Name="Simulation" Type="Folder">
			<Item Name="ArrayToProtocol.vi" Type="VI" URL="../ArrayToProtocol.vi"/>
			<Item Name="SimulatedToArray.vi" Type="VI" URL="../SimulatedToArray.vi"/>
		</Item>
		<Item Name="TopLevel.vi" Type="VI" URL="../TopLevel.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
