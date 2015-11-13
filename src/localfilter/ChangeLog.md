# 2015-05-03  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added forgeSendingData method (to fix an issue with the change action and the global filter)
### Fixed
- fixed an issue in forgeInterfaceTable method
- fixed an issue with the change action (on the sending data)


# 2015-04-29  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added mechanism to handle PutReq messages


# 2015-04-19  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added forgeInterfaceTable method, used to interpose correctly the local filter between layer 3 and layer 2 


# 2015-04-15  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Changed
- changed send handling


# 2015-04-13  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Changed
- changed minor detail in send handling


# 2015-04-12  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added send handling


# 2015-04-09  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added clone handling
- added change handling


# 2015-03-15  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added conditionalAttackEnabled (object attribute) to handle the enabled conditional attacks
- added the handling mechanism of conditional attacks, each conditional attack is attached to the relative self message
### Changed
- changed the handling mechanism of physical attacks, now each physical attack is attached to the relative self message
### Removed
- removed physicalAttack vector (object attribute), no longer needed
- removed conditionalAttack vector (object attribute), no longer needed
- removed sortByOccurrenceTime method, no longer needed


# 2015-03-13  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added gates to connect the local filter to the udp app
### Changed
- changed handleMessage to handle conditional attacks
- changed initializeAttacks to handle conditional attacks


# 2015-03-13  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added gates to connect the local filter to the tcp app
- added gates to connect the local filter to the sctp app
# Changed
- changed initializeGates method to support the tcp and sctp gates


# 2015-03-13  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added gates to connect the local filter to the udp app
- added coupledGates to suport the initialization of the connected gates
- added initializeGates method
### Changed
- changed handleMessages method to extend the capabilities of the local filter 


# 2015-03-11  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Changed
- changed handleMessages method to execute physical attacks


# 2015-03-04  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Fixed
- fixed minor issues in initializeAttack method


# 2015-02-26  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added vectors to support physical and conditional attacks
- added sortByTime method to sort the attack vectors by the occurrence time
- added initializeAttack method to initialize the attack vectors
- added friend class Destroy
### Changed
- changed constructor


# 2015-02-25  Francesco Racciatti  <racciatti.francesco@gmail.com>
## [Unreleased]
### Added
- added LocalFilter.h, LocalFilter.cc, LocalFilter.ned
- added constructor and destructor
- added simple module
