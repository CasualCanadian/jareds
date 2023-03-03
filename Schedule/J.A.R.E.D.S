<?xml version="1.0" encoding="UTF-8"?><project name="J.A.R.E.D.S Timeline" company="" webLink="http://" view-date="2021-05-12" view-index="0" gantt-divider-location="427" resource-divider-location="300" version="3.0.3005" locale="en_CA">
    <description>
        <![CDATA[Scheduled tasks for J.A.R.E.D.S.]]>
    </description>
    <view zooming-state="default:3" id="gantt-chart">
        <field id="tpd3" name="Name" width="210" order="0"/>
        <field id="tpd4" name="Begin date" width="107" order="1"/>
        <field id="tpd5" name="End date" width="106" order="2"/>
        <timeline>
            <![CDATA[74]]>
        </timeline>
    </view>
    <view id="resource-table">
        <field id="0" name="Name" width="210" order="0"/>
        <field id="1" name="Default role" width="86" order="1"/>
    </view>
    <!-- -->
    <calendars>
        <day-types>
            <day-type id="0"/>
            <day-type id="1"/>
            <default-week id="1" name="default" sun="1" mon="0" tue="0" wed="0" thu="0" fri="0" sat="1"/>
            <only-show-weekends value="false"/>
            <overriden-day-types/>
            <days/>
        </day-types>
    </calendars>
    <tasks empty-milestones="true">
        <taskproperties>
            <taskproperty id="tpd0" name="type" type="default" valuetype="icon"/>
            <taskproperty id="tpd1" name="priority" type="default" valuetype="icon"/>
            <taskproperty id="tpd2" name="info" type="default" valuetype="icon"/>
            <taskproperty id="tpd3" name="name" type="default" valuetype="text"/>
            <taskproperty id="tpd4" name="begindate" type="default" valuetype="date"/>
            <taskproperty id="tpd5" name="enddate" type="default" valuetype="date"/>
            <taskproperty id="tpd6" name="duration" type="default" valuetype="int"/>
            <taskproperty id="tpd7" name="completion" type="default" valuetype="int"/>
            <taskproperty id="tpd8" name="coordinator" type="default" valuetype="text"/>
            <taskproperty id="tpd9" name="predecessorsr" type="default" valuetype="text"/>
        </taskproperties>
        <task id="72" name="3D Printing" color="#8cb6ce" meeting="false" start="2021-05-17" duration="15" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" priority="3" expand="true">
            <notes>
                <![CDATA[Design/3D Print any necessary parts for functionality/ergonomics/aesthetics.]]>
            </notes>
        </task>
        <task id="4" name="Gun Hardware" color="#8cb6ce" meeting="false" start="2021-05-17" duration="5" complete="0" thirdDate="2021-05-03" thirdDate-constraint="0" expand="true">
            <notes>
                <![CDATA[Modify Nerf gun, implement new hardware components and schematic.]]>
            </notes>
        </task>
        <task id="74" name="Gun Hardware Complete" color="#8cb6ce" meeting="true" start="2021-05-24" duration="0" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" priority="2" expand="true"/>
        <task id="6" name="Structure Gun Firmware" color="#8cb6ce" meeting="false" start="2021-05-20" duration="4" complete="0" thirdDate="2021-05-12" thirdDate-constraint="0" expand="true">
            <notes>
                <![CDATA[Program Arduino for basic functionality, debug system. Begin structuing code for later.]]>
            </notes>
        </task>
        <task id="9" name="Frame" color="#8cb6ce" meeting="false" start="2021-05-24" duration="5" complete="0" thirdDate="2021-05-12" thirdDate-constraint="0" priority="2" expand="true">
            <notes>
                <![CDATA[Construct frame, test servos.]]>
            </notes>
        </task>
        <task id="10" name="Structure Frame Firmware" color="#8cb6ce" meeting="false" start="2021-05-26" duration="5" complete="0" thirdDate="2021-05-12" thirdDate-constraint="0" priority="2" expand="true">
            <notes>
                <![CDATA[Program Arduino for basic functionality, debug system. Begin structuing code for later. Tune servos for movement.]]>
            </notes>
        </task>
        <task id="77" name="Frame Complete" color="#8cb6ce" meeting="true" start="2021-05-31" duration="0" complete="0" thirdDate="2021-05-12" thirdDate-constraint="0" priority="2" expand="true"/>
        <task id="143" name="Gun Firmware" color="#8cb6ce" meeting="false" start="2021-06-02" duration="3" complete="0" thirdDate="2021-05-12" thirdDate-constraint="0" expand="true">
            <notes>
                <![CDATA[Finish coding firmware for Nerf gun. Add functionality to all components and debug code.]]>
            </notes>
        </task>
        <task id="60" name="Gun Firmware Complete" color="#8cb6ce" meeting="true" start="2021-06-07" duration="0" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" priority="2" expand="true"/>
        <task id="61" name="Develop Bluetooth Application" color="#8cb6ce" meeting="false" start="2021-06-07" duration="5" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" expand="true">
            <notes>
                <![CDATA[Develop PC Bluetooth application for remote control of the sentry gun.]]>
            </notes>
        </task>
        <task id="17" name="Software" color="#8cb6ce" meeting="false" start="2021-06-07" duration="8" complete="0" thirdDate="2021-05-12" thirdDate-constraint="0" priority="4" expand="true">
            <notes>
                <![CDATA[Develop auto-targeting software on Raspberry Pi using Python. Implement serial communication between Raspberry Pi and Arduino. Program interface for Arduino to communicate with Raspberry Pi, receive data and control servos.]]>
            </notes>
        </task>
        <task id="63" name="Complete Software" color="#8cb6ce" meeting="true" start="2021-06-17" duration="0" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" priority="4" expand="true"/>
        <task id="18" name="Testing/Debugging" color="#8cb6ce" meeting="false" start="2021-06-14" duration="5" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" priority="2" expand="true">
            <notes>
                <![CDATA[Final testing/debugging for reliable operation.]]>
            </notes>
        </task>
        <task id="21" name="Complete Project" color="#8cb6ce" meeting="true" start="2021-06-21" duration="0" complete="0" thirdDate="2021-05-10" thirdDate-constraint="0" priority="4" expand="true"/>
    </tasks>
    <resources>
        <resource id="0" name="Gabriel Carey" function="Default:1" contacts="gabe.timothy@gmail.com" phone="613-406-2958"/>
    </resources>
    <allocations>
        <allocation task-id="4" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="6" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="21" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="18" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="63" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="61" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="9" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="72" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="74" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="77" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="60" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="17" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
        <allocation task-id="143" resource-id="0" function="Default:1" responsible="true" load="100.0"/>
    </allocations>
    <vacations/>
    <previous/>
    <roles roleset-name="Default"/>
    <roles roleset-name="SoftwareDevelopment"/>
</project>
