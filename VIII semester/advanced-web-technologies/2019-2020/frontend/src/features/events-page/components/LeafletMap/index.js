import React from 'react';

import { Map, Marker, Popup, TileLayer } from 'react-leaflet';
import { OpenStreetMapProvider } from 'leaflet-geosearch';

import './style.css';

const provider = new OpenStreetMapProvider({ params: { limit: 1 } });

class LeafletMap extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      found: false,
      x: 0,
      y: 0,
    };
  }

  async componentDidMount() {
    if (this.props.address) {
      await this.getLongLat();
    }
  }

  async componentDidUpdate(prevProps) {
    if (prevProps.address !== this.props.address) {
      this.setState({ found: false });
      await this.getLongLat();
    }
  }

  getLongLat = async () => {
    const result = await provider.search({ query: this.props.address });
    result[0] ? this.setState({ x: result[0].x, y: result[0].y, found: true }) : this.setState({ x: -20, y: -20, found: false });
  };

  render() {
    return (
      <Map
        center={[this.state.y, this.state.x]}
        zoom={16}
        // maxZoom = {18}
        // attributionControl={true}
        // zoomCntrol={true}
        // doubleClickZoom={true}
        // scrollWheelZoom={true}
        // dragging={true}
        // animate={true}
        // easeLinearity={0.35}
      >
        <TileLayer url="http://{s}.tile.osm.org/{z}/{x}/{y}.png" />
        <Marker position={[this.state.y, this.state.x]}>
          <Popup>{this.state.found ? this.props.address : 'Address not found'}</Popup>
        </Marker>
      </Map>
    );
  }
}

export default LeafletMap;
