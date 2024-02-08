function dummyFunction(arg = null) {
  console.log("no dragons here...");
}

var authenticate = dummyFunction;
var openLinkInBrowser = dummyFunction;

function setCurrentRoute(route) {
  window.ngAppComponent.zone.run(() => {
    window.ngAppComponent._setCurrentRoute(route);
  });
}

function setLoadingStatus(status) {
  // Wait for component to load
  setTimeout(() => {
    window.ngLoadingComponent.zone.run(() => {
      window.ngLoadingComponent._setLoadingStatus(status);
    });
  });
}
