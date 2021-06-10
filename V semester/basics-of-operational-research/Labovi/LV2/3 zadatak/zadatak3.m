function varargout = zadatak3(varargin)
% ZADATAK3 MATLAB code for zadatak3.fig
%      ZADATAK3, by itself, creates a new ZADATAK3 or raises the existing
%      singleton*.
%
%      H = ZADATAK3 returns the handle to a new ZADATAK3 or the handle to
%      the existing singleton*.
%
%      ZADATAK3('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ZADATAK3.M with the given input arguments.
%
%      ZADATAK3('Property','Value',...) creates a new ZADATAK3 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before zadatak3_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to zadatak3_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help zadatak3

% Last Modified by GUIDE v2.5 15-Oct-2018 15:03:10

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @zadatak3_OpeningFcn, ...
                   'gui_OutputFcn',  @zadatak3_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before zadatak3 is made visible.
function zadatak3_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to zadatak3 (see VARARGIN)

% Choose default command line output for zadatak3
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes zadatak3 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = zadatak3_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
arg1 = str2num(get(handles.edit1,'string'))
arg2 = str2num(get(handles.edit2,'string'))
[zbir, razlika] = zbir_razlika(arg1, arg2);

text_to_display = cellstr(num2str(zbir));
set(handles.text2, 'String', text_to_display, 'Max', 2, 'FontName', 'courier')
text_to_display = cellstr(num2str(razlika));
set(handles.text3, 'String', text_to_display, 'Max', 2, 'FontName', 'courier')


function [zbir,razlika] = zbir_razlika(arg1, arg2)

% prima dva argumenta i 
% racuna zbir i razliku  arg1 i arg2 i vraca njihove vrijednosti 
% ukoliko su prazni argument ili empty uzima se default value 0

[m1,n1] = size(arg1);
[m2,n2] = size(arg2);

if (nargin < 2) || isempty(arg2)
   arg2 = 0;
end
if (nargin < 1) || isempty(arg2)
   arg1 = 0;
end

if (isempty(n1) == false)
    if(isempty(n2)) 
        arg1 = 0;
        arg2 = 0;
    end
    if((m1 ~= m2))
        arg1 = 0;
        arg2 = 0;
    end
end

zbir = arg1 + arg2
razlika = arg1 - arg2
