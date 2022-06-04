pragma solidity 0.5.0;

import "contracts/KittenRegistry.sol";

contract KittyShelter {
    event Transfer(address indexed _from, address indexed _to, uint256 indexed _catId);    
    mapping (uint256 => uint256) private _times;
    mapping (uint256 => address) private _owners;
    address owner;
    KittenRegistry _registry;
    
    constructor (KittenRegistry registry) public {
        _registry = registry;
        owner = msg.sender;
    }
    
    function storeKitty(uint256 catId, uint256 time) public{
        require(_registry.ownerOf(catId) == owner);
        _owners[catId] = owner;
        _times[catId] = time + now;
    }

    function retrieveKitty(uint256 catId) public{
        require(_times[catId] == now);
        _registry.transferFrom(owner, owner, catId);
    }
}