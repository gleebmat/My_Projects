
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Tabs as RadixThemesTabs} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Tabsroot_tabs__root_4b453d635be525f4159efb877cb06270 = memo(({children}) => {
    const on_change_598a768bdff8b92539db087f6f91f906 = useCallback(((_ev_0) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.clear_error", ({  }), ({  })))], [_ev_0], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesTabs.Root,{css:({ ["&[data-orientation='vertical']"] : ({ ["display"] : "flex" }), ["width"] : "100%" }),defaultValue:"login",onValueChange:on_change_598a768bdff8b92539db087f6f91f906},children)
    )
});
