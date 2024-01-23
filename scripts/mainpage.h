/**

    @mainpage

    The goal of DBusMenu is to expose menus on DBus.
    
    Main interface is documented here: @ref com::canonical::dbusmenu
    
 */
/**

		A DBus interface to expose menus on DBus.

		Menu items are represented with a unique numeric id and a dictionary of
		properties.

		To reduce the amount of DBus traffic, a property should only be returned
		if its value is not the default value.

		Available properties are:

		<table>
		<tr>
			<th>Name</th>
			<th>Type</th>
			<th>Description</th>
			<th>Default Value</th>
		</tr>
		<tr>
			<td>type</td>
			<td>String</td>
			<td>Can be one of:
			- "standard": an item which can be clicked to trigger an action or
			  show another menu
			- "separator": a separator

			Vendor specific types can be added by prefixing them with
			"x-<vendor>-".
			</td>
			<td>"standard"</td>
		</tr>
		<tr>
			<td>label</td>
			<td>string</td>
			<td>Text of the item, except that:
			-# two consecutive underscore characters "__" are displayed as a
			single underscore,
			-# any remaining underscore characters are not displayed at all,
			-# the first of those remaining underscore characters (unless it is
			the last character in the string) indicates that the following
			character is the access key.
			</td>
			<td>""</td>
		</tr>
		<tr>
			<td>enabled</td>
			<td>boolean</td>
			<td>Whether the item can be activated or not.</td>
			<td>true</td>
		</tr>
		<tr>
			<td>visible</td>
			<td>boolean</td>
			<td>True if the item is visible in the menu.</td>
			<td>true</td>
		</tr>
		<tr>
			<td>icon-name</td>
			<td>string</td>
			<td>Icon name of the item, following the freedesktop.org icon spec.</td>
			<td>""</td>
		</tr>
		<tr>
			<td>icon-data</td>
			<td>binary</td>
			<td>PNG data of the icon.</td>
			<td>Empty</td>
		</tr>
		<tr>
			<td>shortcut</td>
			<td>array of arrays of strings</td>
			<td>The shortcut of the item. Each array represents the key press
			in the list of keypresses. Each list of strings contains a list of
			modifiers and then the key that is used. The modifier strings
			allowed are: "Control", "Alt", "Shift" and "Super".

			- A simple shortcut like Ctrl+S is represented as:
			  [["Control", "S"]]
			- A complex shortcut like Ctrl+Q, Alt+X is represented as:
			  [["Control", "Q"], ["Alt", "X"]]</td>
			<td>Empty</td>
		</tr>
		<tr>
			<td>toggle-type</td>
			<td>string</td>
			<td>
			If the item can be toggled, this property should be set to:
			- "checkmark": Item is an independent togglable item
			- "radio": Item is part of a group where only one item can be
			  toggled at a time
			- "": Item cannot be toggled
			</td>
			<td>""</td>
		</tr>
		<tr>
			<td>toggle-state</td>
			<td>int</td>
			<td>
			Describe the current state of a "togglable" item. Can be one of:
			- 0 = off
			- 1 = on
			- anything else = indeterminate

			Note:
			The implementation does not itself handle ensuring that only one
			item in a radio group is set to "on", or that a group does not have
			"on" and "indeterminate" items simultaneously; maintaining this
			policy is up to the toolkit wrappers.
			</td>
			<td>-1</td>
		</tr>
		<tr>
			<td>children-display</td>
			<td>string</td>
			<td>
			If the menu item has children this property should be set to
			"submenu".
			</td>
			<td>""</td>
		</tr>
		</table>

		Vendor specific properties can be added by prefixing them with
		"x-<vendor>-".
		
 */
class com.canonical.dbusmenu {
public:
/**

			  Provides the layout and propertiers that are attached to the entries
			  that are in the layout.  It only gives the items that are children
			  of the item that is specified in @a parentId.  It will return all of the
			  properties or specific ones depending of the value in @a propertyNames.

			  The format is recursive, where the second 'v' is in the same format
			  as the original 'a(ia{sv}av)'.  Its content depends on the value
			  of @a recursionDepth.
			
@param[in] parentId The ID of the parent node for the layout.  For
				grabbing the layout from the root node use zero.
@param[in] recursionDepth 
				  The amount of levels of recursion to use.  This affects the
				  content of the second variant array.
				  - -1: deliver all the items under the @a parentId.
				  - 0: no recursion, the array will be empty.
				  - n: array will contains items up to 'n' level depth.
				
@param[in] propertyNames 
					The list of item properties we are
					interested in.  If there are no entries in the list all of
					the properties will be sent.
				
@param[out] revision The revision number of the layout.  For matching
				with layoutUpdated signals.
@param[out] layout The layout, as a recursive structure.
 */
void GetLayout(Int32 parentId, Int32 recursionDepth, Array<String> propertyNames, UInt32 revision, Struct<Int32,Dict<String,Variant>,Array<Variant>> layout);
/**

			Returns the list of items which are children of @a parentId.
			
@param[in] ids 
					A list of ids that we should be finding the properties
					on.  If the list is empty, all menu items should be sent.
				
@param[in] propertyNames 
					The list of item properties we are
					interested in.  If there are no entries in the list all of
					the properties will be sent.
				
@param[out] properties 
					An array of property values.
					An item in this area is represented as a struct following
					this format:
					@li id unsigned the item id
					@li properties map(string => variant) the requested item properties
				
 */
void GetGroupProperties(Array<Int32> ids, Array<String> propertyNames, Array<Struct<Int32,Dict<String,Variant>>> properties);
/**

			  Get a signal property on a single item.  This is not useful if you're
			  going to implement this interface, it should only be used if you're
			  debugging via a commandline tool.
			
@param[in] id the id of the item which received the event
@param[in] name the name of the property to get
@param[out] value the value of the property
 */
void GetProperty(Int32 id, String name, Variant value);
/**

			This is called by the applet to notify the application an event happened on a
			menu item.

			@a type can be one of the following:

			@li "clicked"
			@li "hovered"

			Vendor specific events can be added by prefixing them with "x-<vendor>-"
			
@param[in] id the id of the item which received the event
@param[in] eventId the type of event
@param[in] data event-specific data
@param[in] timestamp The time that the event occured if available or the time the message was sent if not
 */
void Event(Int32 id, String eventId, Variant data, UInt32 timestamp);
/**

			This is called by the applet to notify the application that it is about
			to show the menu under the specified item.
			
@param[in] id 
				Which menu item represents the parent of the item about to be shown.
				
@param[out] needUpdate 
				Whether this AboutToShow event should result in the menu being updated.
				
 */
void AboutToShow(Int32 id, Boolean needUpdate);
signals:
/**

			Triggered when there are lots of property updates across many items
			so they all get grouped into a single dbus message.  The format is
			the ID of the item with a hashtable of names and values for those
			properties.
			
@param[out] updatedProps 
@param[out] removedProps 
 */
void ItemsPropertiesUpdated(Array<Struct<Int32,Dict<String,Variant>>> updatedProps, Array<Struct<Int32,Array<String>>> removedProps);
/**

			Triggered by the application to notify display of a layout update, up to
			revision
			
@param[out] revision The revision of the layout that we're currently on
@param[out] parent 
				If the layout update is only of a subtree, this is the
				parent item for the entries that have changed.  It is zero if
				the whole layout should be considered invalid.
				
 */
void LayoutUpdated(UInt32 revision, Int32 parent);
/**

			  The server is requesting that all clients displaying this
			  menu open it to the user.  This would be for things like
			  hotkeys that when the user presses them the menu should
			  open and display itself to the user.
			
@param[out] id ID of the menu that should be activated
@param[out] timestamp The time that the event occured
 */
void ItemActivationRequested(Int32 id, UInt32 timestamp);
/**
@property Version

			Provides the version of the DBusmenu API that this API is
			implementing.
			

 @par Access: read
 */
Q_PROPERTY(UInt32 Version READ version)
/**
@property Status

            Tells if the menus are in a normal state or they believe that they
            could use some attention.  Cases for showing them would be if help
            were referring to them or they accessors were being highlighted.
            This property can have two values: "normal" in almost all cases and
            "notice" when they should have a higher priority to be shown.
            

 @par Access: read
 */
Q_PROPERTY(String Status READ status)
};
